
#include <pspkernel.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <pspaudio.h>
#include <psputility_netmodules.h>
#include <stdarg.h>
#include <pspnet_apctl.h>
#include <pspgu.h>
#include <psputility.h>
#include <psputility_netconf.h>
#include <pspsdk.h>
#include <stdio.h>
#include <string.h>

#include "../SIPEngine/sipengineif.h"

PSP_MODULE_INFO("SIPPhone", 0, 1, 0);

PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);
PSP_MAIN_THREAD_STACK_SIZE_KB(512);
PSP_HEAP_SIZE_KB(2*1024);

#define WELCOME_MSG "PSP SIP Phone - homebrew wins again!\n"

#define WAV_HEADER_SIZE 0x2c

static unsigned int __attribute__((aligned(16))) list[262144];

int connect_to_apctl(int config);
int LoadModules(void);
int UnloadModules(void);
void DisplayMenu(void);
void cleanScreenRect(int x, int y, int cx, int cy);
void setRedraw(int);
void displayCallState(void);
void displaySIPState(void);
void clearStatusBox();
void displayStatusLines(void);
void statusMessage(const char * msg, ...);
void playRinger(void);
void stopRinger(void);
void initAudio(void);


int CallbackEventHandler(int EventID, ...);

Contact *gContacts = 0;
int gContactsCount = 0;
int gCurrentState = 0;
char gCaller[100];
char gCallee[100];
int gCallerIndex = -1;
int gStartup = 0;
int gCurPos = 0;
SceUID sipModId = 0;
int quit = 0;
int redraw = 0;

#define STATUS_BOX_LEFT   0
#define STATUS_BOX_RIGHT  67
#define STATUS_BOX_TOP    25
#define STATUS_BOX_BOTTOM 32
#define MAX_STATUS_LINES  (STATUS_BOX_BOTTOM - STATUS_BOX_TOP + 1)
char gStatusLines[MAX_STATUS_LINES][69];
int gNumStatusLines;

unsigned short ringbuffer[1024];
SceUID ringThid = 0;
int audio_channel_ring;
SceUID ringfile = -1;
int ringing = 0;

int showInfos = 0;

/* Exit callback */
int exitCallback(int arg1, int arg2, void *common) 
{
	quit = 1;

	return 0;
}

/* Callback thread */
int callbackThread(SceSize args, void *argp) 
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", (void*) exitCallback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();

	return 0;
}

/* Sets up the callback thread and returns its thread id */
int setupCallbacks(void) 
{
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", callbackThread, 0x11, 0xFA0, 0, 0);
	if (thid >= 0) {
		sceKernelStartThread(thid, 0, 0);
	}
	return thid;
}

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)
#define PIXEL_SIZE (4)
#define FRAME_SIZE (BUF_WIDTH * SCR_HEIGHT * PIXEL_SIZE)
#define ZBUF_SIZE (BUF_WIDTH SCR_HEIGHT * 2)

static void setupGu()
{
	sceGuInit();

    sceGuStart(GU_DIRECT,list);
    sceGuDrawBuffer(GU_PSM_8888,(void*)0,BUF_WIDTH);
    sceGuDispBuffer(SCR_WIDTH,SCR_HEIGHT,(void*)0x88000,BUF_WIDTH);
    sceGuDepthBuffer((void*)0x110000,BUF_WIDTH);
    sceGuOffset(2048 - (SCR_WIDTH/2),2048 - (SCR_HEIGHT/2));
    sceGuViewport(2048,2048,SCR_WIDTH,SCR_HEIGHT);
    sceGuDepthRange(0xc350,0x2710);
    sceGuScissor(0,0,SCR_WIDTH,SCR_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);
    sceGuDepthFunc(GU_GEQUAL);
    sceGuEnable(GU_DEPTH_TEST);
    sceGuFrontFace(GU_CW);
    sceGuShadeModel(GU_SMOOTH);
    sceGuEnable(GU_CULL_FACE);
    sceGuEnable(GU_CLIP_PLANES);
    sceGuFinish();
    sceGuSync(0,0);

    sceDisplayWaitVblankStart();
    sceGuDisplay(GU_TRUE);
}

// Allow the extra unknown data entries, otherwise WPA does not work
typedef struct _pspUtilityNetconfData380
{
        pspUtilityDialogCommon base;
        int action; /** One of pspUtilityNetconfActions */
        u32 unknown;
        u32 unknown1;
        u32 unknown2;
} pspUtilityNetconfData380;

pspUtilityNetconfData380 data;

int main(void)
{
	int old_buttons = 0;
	int done = 0;

	SceCtrlData pad;
	pad.Buttons = 0;

	setupCallbacks();

	setupGu();

	LoadModules();
	pspSdkInetInit();
	
	memset(&data, 0, sizeof(data));
	data.base.size = sizeof(data);
	data.base.language = PSP_SYSTEMPARAM_LANGUAGE_ENGLISH;
	data.base.buttonSwap = PSP_UTILITY_ACCEPT_CROSS;
	data.base.graphicsThread = 17;
	data.base.unknown = 19;
	data.base.fontThread = 18;
	data.base.soundThread = 16;
	data.action = PSP_NETCONF_ACTION_CONNECTAP;

	sceUtilityNetconfInitStart((pspUtilityNetconfData*)&data);
	
	while(!done)
	{
		sceGuStart(GU_DIRECT, list);
		sceGuClearColor(0xff554433);
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
		sceGuFinish();
		sceGuSync(0,0);

		switch(sceUtilityNetconfGetStatus())
		{
			case PSP_UTILITY_DIALOG_NONE:
				break;

			case PSP_UTILITY_DIALOG_VISIBLE:
				sceUtilityNetconfUpdate(1);
				break;

			case PSP_UTILITY_DIALOG_QUIT:
				sceUtilityNetconfShutdownStart();
				done = 1;
				break;

			default:
				break;
		}

		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();
	}

	initAudio();
	
	sipModId = pspSdkLoadStartModule("SIPEngine.prx", 2);
	
	pspDebugScreenInit();
	
	pspDebugScreenPrintf(WELCOME_MSG);
	pspDebugScreenPrintf("Build - GUI(%s), Engine(%s)\n", BUILDVERSION, SIPEngineGetBuild());
	
	clearStatusBox();

	statusMessage("Initializing camera... (please ensure it is plugged in)");

	if (SIPEngineInitialize(CallbackEventHandler) < 0)
	{
		statusMessage("Failed to initialize the SIPEngine");
		while(!quit)
		{
			sceKernelDelayThread(1000);
		}
		sceKernelExitGame();
	}

	setRedraw(1);
	
	while (!quit)
	{
//		cleanScreenRect(0,0,68,34);
		
		sceDisplayWaitVblankStart();

    sceCtrlPeekBufferPositive(&pad, 1);
		if (pad.Buttons != old_buttons)
		{
			switch (gCurrentState)
			{
				case SUI_SIP_STATE_CONNECTED:
				{
					switch (pad.Buttons)
					{
						case PSP_CTRL_CROSS:
						{
							clearStatusBox();
							statusMessage("Attempting call");
							strcpy(gCallee, gContacts[gCurPos].nickname);
							SIPEngineDoEvent(SUI_OUT_EVENT_NEW_CALL, gContacts[gCurPos].sipuri);
							setRedraw(1);
							break;
						}
						case PSP_CTRL_DOWN:
						{
							gCurPos++;
							gCurPos %= gContactsCount;
							setRedraw(1);
							break;
						}
						case PSP_CTRL_UP:
						{
							gCurPos--;
							if (gCurPos < 0)
							{
								gCurPos = gContactsCount-1;
							}
							setRedraw(1);
							break;
						}
					}
					break;
				}

				case SUI_SIP_STATE_TRYING:
				{
					switch (pad.Buttons)
					{
						case PSP_CTRL_CIRCLE:
						{
							SIPEngineDoEvent(SUI_OUT_EVENT_REJECT);
						  statusMessage("Cancelling...");
							gCallee[0] = '\0';
							setRedraw(1);
							break;
						}
					}
					break;
				}

				case SUI_SIP_STATE_INCOMING:
				{
					switch (pad.Buttons)
					{
						case PSP_CTRL_CIRCLE:
						{
							SIPEngineDoEvent(SUI_OUT_EVENT_REJECT);
						  statusMessage("Rejecting...");
							setRedraw(1);
							break;
						}
						case PSP_CTRL_CROSS:
						{
							SIPEngineDoEvent(SUI_OUT_EVENT_ANSWER);
							statusMessage("Answering...");
							setRedraw(1);
							break;
						}
					}
					break;
				}

				case SUI_SIP_STATE_ESTABLISHED:
				{
					switch (pad.Buttons)
					{
						case PSP_CTRL_TRIANGLE:
						{
							SIPEngineDoEvent(SUI_OUT_EVENT_HANGUP);
							clearStatusBox();
							statusMessage("Call disconnected.");
							setRedraw(1);
							break;
						}
					}
					
					break;
				}
			}
			
			/* Global key bindings */
			if (pad.Buttons == PSP_CTRL_START)
			{
				quit = 1;
			}
			else if (pad.Buttons == PSP_CTRL_SELECT)
			{
				showInfos = !showInfos;
				if (showInfos)
				{
					statusMessage("Extra informational messages ENABLED");
				}
				else
				{
					statusMessage("Extra informational messages DISABLED");
				}
			}
			
			/* wait for key to be released */
			while ((pad.Buttons != old_buttons) && !quit)
			{
				sceKernelDelayThread(1000);
				sceCtrlPeekBufferPositive(&pad, 1);
			}
		}

	  DisplayMenu();
	}
	
	statusMessage("Quitting...");
	SIPEngineDoEvent(SUI_OUT_EVENT_SHUTDOWN);

	sceKernelExitGame();
	return 0;
}

int CallbackEventHandler(int EventID, ...)
{
//	pspDebugScreenPrintf("callback event: %d\n", EventID);
	int rc = 0;
	
	va_list argp;
	va_start(argp, EventID);	

	switch (EventID)
	{
		case SUI_IN_EVENT_SIP_STATE:
		{
			int lNewState = va_arg(argp, int);
			/* If we've gone from calling to not calling, show a status message */
			if ((gCurrentState > SUI_SIP_STATE_CONNECTED) &&
					(lNewState <= SUI_SIP_STATE_CONNECTED))
			{
				clearStatusBox();
				statusMessage("Call cancelled");
			}
			
			if ((lNewState == SUI_SIP_STATE_ESTABLISHED) ||
					(lNewState == SUI_SIP_STATE_CONNECTED))
			{
				stopRinger();
			}
			
			/* A few messages to tidy up the appearance for certain
			   state change events */
			if (lNewState == SUI_SIP_STATE_ESTABLISHED)
			{
				clearStatusBox();
				statusMessage("Call established");
			}
			
			gCurrentState = lNewState;

			if (gCurrentState == SUI_SIP_STATE_CONNECTED)
			{
				memset(gCaller, 0, sizeof(gCaller));
				gCallerIndex = -1;
			}
			
			setRedraw(1);
			// reflected in the menu.

			break;
		}

		case SUI_IN_EVENT_INCOMING_CALL:
		{
			playRinger();
			char *caller = va_arg(argp, char *);
			if (caller)
			{
				strcpy(gCaller, caller);
			}
			else
			{
				strcpy(gCaller, "Unknown");
			}

			gCallerIndex = va_arg(argp, int);
			
			statusMessage("Incoming call... %s", gCaller);
			
			setRedraw(1);
			// Announced later in the menu
			
			break;
		}

		case SUI_IN_EVENT_STARTUP:
		{
			pspDebugScreenSetXY(20, 20);

			gStartup = va_arg(argp, int);
			
			switch (gStartup)
			{
				case 0:
			  {
				  statusMessage("Starting up...");
			  }
				break;
				
				case 1:
				{
					statusMessage("Registering with server...");
				}
				break;
				
				case 2:
				{
					clearStatusBox();
					statusMessage("Ready.");
				}
				break;
				
				default:
				{
					statusMessage("Startup state: %d", gStartup);
				}
				break;
			}
				
			break;
		}

		case SUI_IN_ADDRESS_BOOK:
		{
			gContacts = va_arg(argp, Contact *);
			gContactsCount = va_arg(argp, int);
			
			statusMessage("Processed address book : %d contacts", gContactsCount);

			break;
		}
		
		case SUI_IN_INFO_MESSAGE:
		{
			if (showInfos)
			{
				char *lmsg = va_arg(argp, char*);
				statusMessage(lmsg);
			}
			break;
		}
		
		case SUI_IN_ERROR_MESSAGE:
		{
			char *lmsg = va_arg(argp, char*);
			statusMessage(lmsg);
			sceKernelDelayThread(1 * 1000 * 1000);
			break;
		}
	}

	va_end(argp);

	return rc;
}

void setRedraw(int val)
{
	
	redraw = val;
}

void DisplayMenu(void)
{
	if (!redraw)
	{
		return;
	}
	
	int i;
	
	cleanScreenRect(0,3,68,STATUS_BOX_TOP - 5);
	pspDebugScreenSetXY(0, 3);
	switch (gCurrentState)
	{
		case SUI_SIP_STATE_CONNECTED:
		{
			pspDebugScreenPrintf("Please choose a contact and press X to dial.");
			cleanScreenRect(3,6,68,gContactsCount);
			for (i=0; i<gContactsCount; i++)
			{
				pspDebugScreenSetXY(3, 6+i);
				if (gContacts)
				{
					if (gContacts[i].nickname)
					{
						pspDebugScreenPrintf("%s %s", 
							(gCurPos == i) ? "*" : " ",
							gContacts[i].nickname);
					}
				}
			}
		}
		break;
		
		case SUI_SIP_STATE_ESTABLISHED:
		{
			pspDebugScreenPrintf("Press triangle to hang up.");
		}
		break;
		
		case SUI_SIP_STATE_TRYING:
		{
			pspDebugScreenPrintf("Attempting call to %s\n", gCallee);
			pspDebugScreenPrintf("Press O to cancel.");
		}
		break;
		
		case SUI_SIP_STATE_INCOMING:
		{
			pspDebugScreenPrintf("Incoming call from %s\n", gCaller);
			pspDebugScreenPrintf("Press X to accept, O to reject.");
		}
		break;
		
		case SUI_SIP_STATE_DISCONNECTED:
		{
			pspDebugScreenPrintf("Please wait while the server is contacted.");
		}
		break;
	}

	displayCallState();
	displaySIPState();

	pspDebugScreenSetXY(0, 10);
	setRedraw(0);
}

/* Connect to an access point */
int connect_to_apctl(int config)
{
	int err;
	int stateLast = -1;
	
	statusMessage("Attempting to connect to network...");

	/* Connect using the first profile */
	err = sceNetApctlConnect(config);
	if (err != 0)
	{
		statusMessage(": sceNetApctlConnect returns %08X", err);
		return 0;
	}

	statusMessage(": Connecting...");
	while (1)
	{
		int state;
		err = sceNetApctlGetState(&state);
		if (err != 0)
		{
			statusMessage(": sceNetApctlGetState returns $%x", err);
			break;
		}
		if (state > stateLast)
		{
			stateLast = state;
		}
		if (state == 4)
			break;  // connected with static IP

		// wait a little before polling again
		sceKernelDelayThread(50*1000); // 50ms
	}
	
	if(err != 0)
	{
  	statusMessage(": Failed to connect!");
		sceKernelDelayThread(1000 * 1000);
		return 0;
	}
	
	statusMessage(": connected!");
	sceKernelDelayThread(200 * 1000);
	clearStatusBox();
	return 1;
}

int LoadModules()
{
	int result = sceUtilityLoadNetModule(PSP_NET_MODULE_COMMON);
	if (result < 0)
	{
		printf("Error 0x%08X loading pspnet.prx.\n", result);
		return result;
	}

	result = sceUtilityLoadNetModule(PSP_NET_MODULE_INET);
	if (result < 0)
	{
		printf("Error 0x%08X loading pspnet_inet.prx.\n", result);
		return result;
	}

	return 0;
}

int UnloadModules()
{
	int result = sceUtilityUnloadNetModule(PSP_NET_MODULE_COMMON);
	if (result < 0)
	{
		printf("Error 0x%08X unloading pspnet.prx.\n", result);
		return result;
	}

	result = sceUtilityUnloadNetModule(PSP_NET_MODULE_INET);
	if (result < 0)
	{
		printf("Error 0x%08X unloading pspnet_inet.prx.\n", result);
		return result;
	}

	return 0;
}

// Clear a rectangle on the screen
void cleanScreenRect(int x, int y, int cx, int cy)
{
	int ii, jj;
	
	for (ii = y; ii < (y+cy); ii++)
	{
		for (jj = x; jj < (x+cx); jj++)
		{
			pspDebugScreenSetXY(jj, ii);
			pspDebugScreenPrintf(" ");
		}
	}
}

void displaySIPState()
{
	cleanScreenRect(40,0,27,1);
	pspDebugScreenSetXY(40,0);
	pspDebugScreenPrintf("Server : ");
	switch (gCurrentState)
	{
		case SUI_SIP_STATE_DISCONNECTED:
		{
			pspDebugScreenPrintf("Not connected");
			break;
		}
		case SUI_SIP_STATE_CONNECTING:
		{
			pspDebugScreenPrintf("Connecting...");
			break;
		}
		case SUI_SIP_STATE_CONNECTED:
		case SUI_SIP_STATE_TRYING:
		case SUI_SIP_STATE_INCOMING:
		case SUI_SIP_STATE_ESTABLISHED:
		{
			pspDebugScreenPrintf("Connected");
			break;
		}
		default:
		{
			pspDebugScreenPrintf("Unknown");
		}
	}
}

void displayCallState()
{
	cleanScreenRect(40,1,27,1);
	pspDebugScreenSetXY(40,1);
	pspDebugScreenPrintf("Call   : ");
	switch (gCurrentState)
	{
		case SUI_SIP_STATE_TRYING:
		{
			pspDebugScreenPrintf("Calling");
			break;
		}
		case SUI_SIP_STATE_INCOMING:
		{
			pspDebugScreenPrintf("Incoming");
			break;
		}
		case SUI_SIP_STATE_ESTABLISHED:
		{
			pspDebugScreenPrintf("Connected");
			break;
		}
		case SUI_SIP_STATE_DISCONNECTED:
		case SUI_SIP_STATE_CONNECTING:
		case SUI_SIP_STATE_CONNECTED:
		{
			pspDebugScreenPrintf("None");
			break;
		}
		default:
		{
			pspDebugScreenPrintf("Unknown");
		}
	}
}

void clearStatusBox()
{
	cleanScreenRect(STATUS_BOX_LEFT,
									STATUS_BOX_TOP,
								  STATUS_BOX_RIGHT - STATUS_BOX_LEFT + 1,
 									STATUS_BOX_BOTTOM - STATUS_BOX_TOP + 1 );
	
	gNumStatusLines = 0;
	int ii;
	for (ii = 0; ii < MAX_STATUS_LINES; ii++)
	{
		gStatusLines[MAX_STATUS_LINES][0] = '\0';
	}
}

void displayStatusLines(void)
{
	int ii;
	
	cleanScreenRect(STATUS_BOX_LEFT,
									STATUS_BOX_TOP,
								  STATUS_BOX_RIGHT - STATUS_BOX_LEFT + 1,
 									STATUS_BOX_BOTTOM - STATUS_BOX_TOP + 1 );
	
	for (ii = 0; ii < gNumStatusLines; ii++)
	{
		pspDebugScreenSetXY(STATUS_BOX_LEFT, STATUS_BOX_TOP + ii);
		pspDebugScreenPrintf(gStatusLines[ii]);
	}
}

void statusMessage(const char * msg, ...)
{
	int ii;
	char lmsg[256];
	
	va_list argp;
	va_start(argp, msg);	
	vsnprintf(lmsg, 256, msg, argp);
	va_end(argp);
	
	/* Do we need to scroll? */
	if (gNumStatusLines < (MAX_STATUS_LINES - 1))
	{
		/* no */
		strcpy(gStatusLines[gNumStatusLines], lmsg);
		gNumStatusLines++;
	}
	else
	{
		/* yes */
		for (ii = 0; ii < (gNumStatusLines - 1); ii++)
		{
			strcpy(gStatusLines[ii], gStatusLines[ii+1]);
		}
		strcpy(gStatusLines[ii], lmsg);
	}
	
	displayStatusLines();
}

int playRingerThread(SceSize args, void *argp)
{
	while (ringing)
	{
		sceIoLseek32(ringfile, WAV_HEADER_SIZE, SEEK_SET);
		int lread;
		while ((lread = sceIoRead(ringfile, ringbuffer, 2048)) && ringing)
		{
			sceAudioOutputBlocking(audio_channel_ring, PSP_AUDIO_VOLUME_MAX, ringbuffer);
		}
		
		if (ringing)
		{
			sceKernelDelayThread(2 * 1000 * 1000);
		}
	}

	sceKernelExitDeleteThread(0);
	return 0;
}

void playRinger(void)
{
	ringing = 1;
	if (ringfile >= 0)
	{
		ringThid = sceKernelCreateThread("AudioRing", playRingerThread, 0x18, 0x10000, 0, NULL);
		sceKernelStartThread(ringThid, 0, 0);
	}
}

void stopRinger(void)
{
	ringing = 0;
}

void initAudio(void)
{
	audio_channel_ring = sceAudioChReserve(PSP_AUDIO_NEXT_CHANNEL,
																			1024,
																			PSP_AUDIO_FORMAT_MONO);
	
	ringfile = sceIoOpen("ring.wav", PSP_O_RDONLY, 0777);
	if (ringfile < 0)
	{
		statusMessage("Error 0x%08X opening ring.wav file", ringfile);
	}
}

