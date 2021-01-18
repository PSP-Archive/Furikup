
#include <pspkernel.h>
#include <pspaudio.h>
#include <psputility_usbmodules.h>
#include <psputility_avmodules.h>
#include <pspsdk.h>
#include <pspusb.h>
#include <pspusbacc.h>
#include <pspusbcam.h>
#include <pspctrl.h>
#include <eXosip2/eXosip.h>
#include <netinet/in.h>
#include <ortp/ortp.h>
#include <ortp/stun.h>
#include "pspmic.h"

#include "config.h"
#include "config_file.h"
#include "audio.h"
#include "video.h"
#include "presence.h"
#include "call_api.h"
#include "sipengine.h"
#include "addressbook.h"

PSP_MODULE_INFO("SIPEngine", 0, 1, 0);

PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);
PSP_HEAP_SIZE_KB(15*1024);
PSP_MAIN_THREAD_STACK_SIZE_KB(512);

int LoadModules(void);
int UnloadModules(void);
int StartUsb(void);
int StopUsb(void);

SUI_OUT_EVENT_FN gEventFunction = 0;
SceUID logfd = 0;

int main(void)
{
	sceKernelExitDeleteThread(0);

	return 0;
}

char trc_buf[2048];

static const char build[100] = BUILDVERSION;

const char *SIPEngineGetBuild(void)
{
	return build;
}

void osip_trace_func(char *fi, int li, osip_trace_level_t level,
                     char *chfr, va_list ap)
{
	int in = 0;

	memset (trc_buf, 0, sizeof (trc_buf));
	if (level == OSIP_FATAL)
		in = snprintf (trc_buf, 2047, "| FATAL | <%s: %i> ", fi, li);
	else if (level == OSIP_BUG)
		in = snprintf (trc_buf, 2047, "|  BUG  | <%s: %i> ", fi, li);
	else if (level == OSIP_ERROR)
		in = snprintf (trc_buf, 2047, "| ERROR | <%s: %i> ", fi, li);
	else if (level == OSIP_WARNING)
		in = snprintf (trc_buf, 2047, "|WARNING| <%s: %i> ", fi, li);
	else if (level == OSIP_INFO1)
		in = snprintf (trc_buf, 2047, "| INFO1 | <%s: %i> ", fi, li);
	else if (level == OSIP_INFO2)
		in = snprintf (trc_buf, 2047, "| INFO2 | <%s: %i> ", fi, li);
	else if (level == OSIP_INFO3)
		in = snprintf (trc_buf, 2047, "| INFO3 | <%s: %i> ", fi, li);
	else if (level == OSIP_INFO4)
		in = snprintf (trc_buf, 2047, "| INFO4 | <%s: %i> ", fi, li);

	vsnprintf (trc_buf + in, 2047 - in, chfr, ap);

	// Pass the errors and warnings across to the GUI
	if (level <= OSIP_WARNING)
	{
		InfoMessage(trc_buf);
	}

	if (logfd > 0)
	{
		sceIoWrite(logfd, trc_buf, strlen(trc_buf));
	}

	printf(trc_buf);
}

int SIPEngineInitialize(SUI_OUT_EVENT_FN callback)
{
	char *logfile = 0;
	int pid;
	int i;
	int result = 0;
	
	gEventFunction = callback;

	parseConfigFile("sipcfg.ini");
	parseAddressbook("contacts.txt");

	logfile = config_get_logfile();

	if(logfile[0] != 0)
	{
		logfd = sceIoOpen(logfile, PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
	}

	result = LoadModules();
	if (result < 0)
	{
		return result;
	}

	if (config_use_usb())
	{
		result = StartUsb();
		if (result < 0)
		{
			return result;
		}

		if (config_get_use_video())
		{
			pid = PSP_USBCAM_PID;
		}
		else
		{
			pid = PSP_USBMIC_PIC;
		}

		result = sceUsbActivate(pid);
		if (result < 0)
		{
			ErrorMessage("Error activating the camera: 0x%08X\n", result);
			return result;
		}
		else
		{
			while (1)
			{
				if ((sceUsbGetState() & 0xF) == PSP_USB_CONNECTION_ESTABLISHED)
					break;

				sceKernelDelayThread(50000);
			}

			if (config_get_use_video())
			{
				initVideo();
			}
		}
	}

	result = initAudio();
	if (result < 0)
	{
		return result;
	}

	i = eXosip_init();
	if (i != 0)
	{
		return -1;
	}

	ortp_init();
	ortp_scheduler_init();
	ortp_set_log_level_mask(ORTP_MESSAGE|ORTP_WARNING|ORTP_ERROR);
	
	osip_trace_initialize_func(OSIP_INFO4, osip_trace_func);

	int temp=1;
	eXosip_set_option(EXOSIP_OPT_EVENT_PACKAGE, &temp);
	eXosip_set_option(EXOSIP_OPT_DONT_SEND_101, &temp);

	i = eXosip_listen_addr (IPPROTO_UDP, NULL, 5060, AF_INET, 0);
	if (i != 0)
	{
		eXosip_quit();
		ErrorMessage("Could not initialize transport layer");
		return -1;
	}

	eXosip_add_authentication_info(config_get_user(), config_get_user(),
							config_get_password(), NULL, NULL);

	// Start the thread for handling all of the SIP and call control
	setupCallThread();

	return 0;
}

int module_stop()
{
//	disconnectSipServer();
	return 0;
}

int LoadModules()
{
	int result;

	result = pspSdkLoadStartModule("AudioFreq.prx", PSP_MEMORY_PARTITION_KERNEL);
	if (result < 0)
	{
		ErrorMessage("Error 0x%08X loading AudioFreq.prx.\n", result);
		return result;
	}

	if (config_use_usb())
	{
		result = sceUtilityLoadUsbModule(PSP_USB_MODULE_ACC);
		if (result < 0)
		{
			ErrorMessage("Error 0x%08X loading usbacc.prx.\n", result);
			return result;
		}

		if (config_get_use_video())
		{
			result = sceUtilityLoadUsbModule(PSP_USB_MODULE_CAM);	
			if (result < 0)
			{
				ErrorMessage("Error 0x%08X loading usbcam.prx.\n", result);
				return result;
			}
		}
		else
		{
			result = sceUtilityLoadUsbModule(PSP_USB_MODULE_MIC);
			if (result < 0)
			{
				ErrorMessage("Error 0x%08X loading usbmic.prx.\n", result);
				return result;
			}
		}
	}

	return result;
}

int UnloadModules()
{
	int result = 0;

	if (config_use_usb())
	{
		if (config_get_use_video())
		{
			result = sceUtilityUnloadUsbModule(PSP_USB_MODULE_CAM);	
			if (result < 0)
			{
				printf("Error 0x%08X loading usbcam.prx.\n", result);
				return result;
			}
		}
		else
		{
			result = sceUtilityUnloadUsbModule(PSP_USB_MODULE_MIC);
			if (result < 0)
			{
				printf("Error 0x%08X loading usbmic.prx.\n", result);
				return result;
			}
		}

		result = sceUtilityUnloadUsbModule(PSP_USB_MODULE_ACC);
		if (result < 0)
		{
			printf("Error 0x%08X loading usbacc.prx.\n", result);
			return result;
		}
	}

	return result;
}

int StartUsb()
{
	int result = sceUsbStart(PSP_USBBUS_DRIVERNAME, 0, 0);
	if (result < 0)
	{
		ErrorMessage("Error 0x%08X starting usbbus driver.\n", result);
		return result;
	}

	result = sceUsbStart(PSP_USBACC_DRIVERNAME, 0, 0);
	if (result < 0)
	{
		ErrorMessage("Error 0x%08X starting usbacc driver.\n", result);
		return result;
	}
	
	if (config_get_use_video())
	{
		result = sceUsbStart(PSP_USBCAM_DRIVERNAME, 0, 0);
		if (result < 0)
		{
			ErrorMessage("Error 0x%08X starting usbcam driver.\n", result);
			return result;
		}

		result = sceUsbStart(PSP_USBCAMMIC_DRIVERNAME, 0, 0);
		if (result < 0)
		{
			ErrorMessage("Error 0x%08X starting usbcammic driver.\n", result);		
		}
	}
	else
	{
		result = sceUsbStart(PSP_USBMIC_DRIVERNAME, 0, 0);
		if (result < 0)
		{
			ErrorMessage("Error 0x%08X starting usbmic driver.\n", result);		
		}
	}

	return result;
}

int StopUsb()
{
	int result = 0;

	if (config_get_use_video())
	{
		result = sceUsbStop(PSP_USBCAMMIC_DRIVERNAME, 0, 0);	
		if (result < 0)
		{
			printf("Error 0x%08X stopping usbcammic driver.\n", result);
			return result;
		}
		
		result = sceUsbStop(PSP_USBCAM_DRIVERNAME, 0, 0);
		if (result < 0)
		{
			printf("Error 0x%08X stopping usbcam driver.\n", result);
			return result;
		}
	}
	else
	{
		result = sceUsbStop(PSP_USBMIC_DRIVERNAME, 0, 0);
		if (result < 0)
		{
			printf("Error 0x%08X stopping usbmic driver.\n", result);
			return result;
		}
	}

	result = sceUsbStop(PSP_USBACC_DRIVERNAME, 0, 0);
	if (result < 0)
	{
		printf("Error 0x%08X stopping usbacc driver.\n", result);
		return result;
	}

	result = sceUsbStop(PSP_USBBUS_DRIVERNAME, 0, 0);
	if (result < 0)
	{
		printf("Error 0x%08X stopping usbbus driver.\n", result);
	}

	return result;
}

/* 
 * Build an info message via printf-like interface (convenience function)
 */
void InfoMessage(const char * fmt, ...)
{
	char msg[256];
	
	va_list argp;
	va_start(argp, fmt);	
	
	vsnprintf(msg, 256, fmt, argp);
	
	va_end(argp);
	
	gEventFunction(SUI_IN_INFO_MESSAGE, msg);
}

/* 
 * Build an error message via printf-like interface (convenience function)
 */
void ErrorMessage(const char * fmt, ...)
{
	char msg[256];
	
	va_list argp;
	va_start(argp, fmt);	
	
	vsnprintf(msg, 256, fmt, argp);
	
	va_end(argp);
	
	gEventFunction(SUI_IN_ERROR_MESSAGE, msg);
}

