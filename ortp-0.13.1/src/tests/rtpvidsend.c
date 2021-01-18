  /*
  The oRTP library is an RTP (Realtime Transport Protocol - rfc3550) stack.
  Copyright (C) 2001  Simon MORLAT simon.morlat@linphone.org

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <ortp/ortp.h>
#include <signal.h>
#include <stdlib.h>

#ifndef _WIN32 
#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#endif

#include <pspkernel.h>
#include <psputility_netmodules.h>
#include <pspctrl.h>
#include <netinet/in.h>
#include <psputility_usbmodules.h>
#include <psputility_avmodules.h>
#include <pspusb.h>
#include <pspusbacc.h>
#include <pspusbcam.h>

#define MAX_VIDEO_FRAME_SIZE	(32*1024)
#define MAX_STILL_IMAGE_SIZE	(512*1024)

static u8  buffer[MAX_STILL_IMAGE_SIZE] __attribute__((aligned(64)));
static u8  work[68*1024] __attribute__((aligned(64)));
static u32 framebuffer[480*272] __attribute__((aligned(64)));

int LoadModules()
{
	int result = sceUtilityLoadUsbModule(PSP_USB_MODULE_ACC);
	if (result < 0)
	{
		printf("Error 0x%08X loading usbacc.prx.\n", result);
		return result;
	}

	result = sceUtilityLoadUsbModule(PSP_USB_MODULE_CAM);	
	if (result < 0)
	{
		printf("Error 0x%08X loading usbcam.prx.\n", result);
		return result;
	}

	// For jpeg decoding
	result = sceUtilityLoadAvModule(PSP_AV_MODULE_AVCODEC);
	if (result < 0)
	{
		printf("Error 0x%08X loading avcodec.prx.\n", result);
	}

	return result;
}

int StartUsb()
{
	int result = sceUsbStart(PSP_USBBUS_DRIVERNAME, 0, 0);
	if (result < 0)
	{
		printf("Error 0x%08X starting usbbus driver.\n", result);
		return result;
	}

	result = sceUsbStart(PSP_USBACC_DRIVERNAME, 0, 0);
	if (result < 0)
	{
		printf("Error 0x%08X starting usbacc driver.\n", result);
		return result;
	}
	
	result = sceUsbStart(PSP_USBCAM_DRIVERNAME, 0, 0);
	if (result < 0)
	{
		printf("Error 0x%08X starting usbcam driver.\n", result);
		return result;
	}

	result = sceUsbStart(PSP_USBCAMMIC_DRIVERNAME, 0, 0);
	if (result < 0)
	{
		printf("Error 0x%08X starting usbcammic driver.\n", result);		
	}

	return result;
}

/* Connect to an access point */
int connect_to_apctl(int config)
{
	int err;
	int stateLast = -1;

	/* Connect using the first profile */
	err = sceNetApctlConnect(config);
	if (err != 0)
	{
		printf(": sceNetApctlConnect returns %08X\n", err);
		return 0;
	}

	printf(": Connecting...\n");
	while (1)
	{
		int state;
		err = sceNetApctlGetState(&state);
		if (err != 0)
		{
			printf(": sceNetApctlGetState returns $%x\n", err);
			break;
		}
		if (state > stateLast)
		{
			printf("  connection state %d of 4\n", state);
			stateLast = state;
		}
		if (state == 4)
			break;  // connected with static IP

		// wait a little before polling again
		sceKernelDelayThread(50*1000); // 50ms
	}
	printf(": Connected!\n");

	if(err != 0)
	{
		return 0;
	}

	return 1;
}

PSP_MODULE_INFO("RTP Timer Test", 0, 1, 0);
PSP_HEAP_SIZE_KB(20*1024);

int runcond=1;

void stophandler(int signum)
{
	runcond=0;
}

static char * _strdup_vprintf(const char *fmt, va_list ap)
{
	/* Guess we need no more than 100 bytes. */
	int n, size = 200;
	char *p,*np;
	//va_list ap;
	if ((p = (char *) ortp_malloc (size)) == NULL)
		return NULL;
	while (1)
	{
		/* Try to print in the allocated space. */
		//va_start(ap, fmt);
		n = vsnprintf (p, size, fmt, ap);
		//va_end(ap);
		/* If that worked, return the string. */
		if (n > -1 && n < size)
			return p;
		//printf("Reallocing space.\n");
		/* Else try again with more space. */
		if (n > -1)	/* glibc 2.1 */
			size = n + 1;	/* precisely what is needed */
		else		/* glibc 2.0 */
			size *= 2;	/* twice the old size */
		if ((np = (char *) ortp_realloc (p, size)) == NULL)
		  {
		    free(p);
		    return NULL;
		  }
		else
		  {
		    p = np;
		  }
	}
}

static void psp_logv_out(OrtpLogLevel lev, const char *fmt, va_list args)
{
	static int temp = 0;

	if (temp++ > 20)
		return;

	const char *lname="undef";
	char *msg;

	switch(lev)
	{
		case ORTP_DEBUG:
			lname="debug";
			break;
		case ORTP_MESSAGE:
			lname="message";
			break;
		case ORTP_WARNING:
			lname="warning";
			break;
		case ORTP_ERROR:
			lname="error";
			break;
		case ORTP_FATAL:
			lname="fatal";
			break;
		default:
			ortp_fatal("Bad level !");
	}

	msg=_strdup_vprintf(fmt,args);
	pspDebugScreenPrintf("ortp-%s-%s\n",lname,msg);
	ortp_free(msg);	
}

static char *help="usage: rtpsend	filename dest_ip4addr dest_port [ --with-clockslide <value> ] [ --with-jitter <milliseconds>]\n";

int main(int argc, char *argv[])
{
	sceUtilityLoadNetModule(PSP_NET_MODULE_COMMON);
	sceUtilityLoadNetModule(PSP_NET_MODULE_INET);

	pspSdkInetInit();
	connect_to_apctl(1);

	pspDebugScreenInit();

	RtpSession *session;
	int i;
	FILE *infile;
	char *ssrc;
	uint32_t user_ts=0;
	int clockslide=0;
	int jitter=0;

	ortp_init();
	ortp_scheduler_init();
	ortp_set_log_level_mask(ORTP_MESSAGE|ORTP_WARNING|ORTP_ERROR);
	ortp_set_log_handler(psp_logv_out);
	session=rtp_session_new(RTP_SESSION_SENDONLY);	
	rtp_session_set_scheduling_mode(session,1);
	rtp_session_set_blocking_mode(session,0);
	rtp_session_set_connected_mode(session,TRUE);
	rtp_session_set_remote_addr(session,"192.168.0.5",6760);
	rtp_session_set_payload_type(session,26);
	
	ssrc=getenv("SSRC");
	if (ssrc!=NULL) {
		printf("using SSRC=%i.\n",atoi(ssrc));
		rtp_session_set_ssrc(session,atoi(ssrc));
	}
	
	if (LoadModules() < 0)
		sceKernelSleepThread();

	if (StartUsb() < 0)
		sceKernelSleepThread();

	if (sceUsbActivate(PSP_USBCAM_PID) < 0)
	{
		printf("Error activating the camera.\n");
		sceKernelSleepThread();
	}

	while (1)
	{
		if ((sceUsbGetState() & 0xF) == PSP_USB_CONNECTION_ESTABLISHED)
			break;

		sceKernelDelayThread(50000);
	}

//	signal(SIGINT,stophandler);
	PspUsbCamSetupVideoParam videoparam;
	int result;
	u32 *vram = (u32 *)0x04000000;

	memset(&videoparam, 0, sizeof(videoparam));
	videoparam.size = sizeof(videoparam);
	videoparam.resolution = PSP_USBCAM_RESOLUTION_160_120;
	videoparam.framerate = PSP_USBCAM_FRAMERATE_15_FPS;
	videoparam.wb = PSP_USBCAM_WB_AUTO;
	videoparam.saturation = 125;
	videoparam.brightness = 128;
	videoparam.contrast = 64;
	videoparam.sharpness = 0;
	videoparam.effectmode = PSP_USBCAM_EFFECTMODE_NORMAL;
	videoparam.framesize = MAX_VIDEO_FRAME_SIZE;
	videoparam.evlevel = PSP_USBCAM_EVLEVEL_0_0;	

	result = sceUsbCamSetupVideo(&videoparam, work, sizeof(work));	
	if (result < 0)
	{
		printf("Error 0x%08X in sceUsbCamSetupVideo.\n", result);
		sceKernelExitDeleteThread(result);
	}

	sceUsbCamAutoImageReverseSW(1);
		pspDebugScreenPrintf("%s, %d\n", __FILE__, __LINE__);

	result = sceUsbCamStartVideo();	
	if (result < 0)
	{
		printf("Error 0x%08X in sceUsbCamStartVideo.\n", result);
		sceKernelExitDeleteThread(result);
	}

	while (1)
	{
		int i, j, m, n;
		
		result = sceUsbCamReadVideoFrameBlocking(buffer, MAX_VIDEO_FRAME_SIZE);
		if (result < 0)
		{
			pspDebugScreenPrintf("Error 0x%08X in sceUsbCamReadVideoFrameBlocking,\n", result);
			continue;
		}
		else
		{
			if(rtp_session_send_with_ts(session, buffer, result, user_ts) < 0)
			{
				pspDebugScreenPrintf("user_ts = %d\n", user_ts);
				for(;;)
					sceDisplayWaitVblankStart();
			}

			user_ts += 6000;
		}
	}
	
	rtp_session_destroy(session);
	ortp_exit();
	ortp_global_stats_display();

	return 0;
}
