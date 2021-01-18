 /*
  The oRTP LinPhone RTP library intends to provide basics for a RTP stack.
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


#include "../rtptimer.h"
#include <stdio.h>


#include <pspkernel.h>
#include <psputility_netmodules.h>
#include <pspctrl.h>
#include <netinet/in.h>


PSP_MODULE_INFO("RTP Timer Test", 0, 1, 0);

int main(int argc, char *argv[])
{
	sceUtilityLoadNetModule(PSP_NET_MODULE_COMMON);
	sceUtilityLoadNetModule(PSP_NET_MODULE_INET);

	pspSdkInetInit();
	connect_to_apctl(1);

	pspDebugScreenInit();

	RtpTimer *timer=&posix_timer;
	int i;
	struct timeval interval;
	
	interval.tv_sec=0;
	interval.tv_usec=500000;
	
	rtp_timer_set_interval(timer,&interval);
	
	timer->timer_init();
	for (i=0;i<10;i++)
	{
		printf("doing something...\n");
		timer->timer_do();
	}
	timer->timer_uninit();
	return 0;
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
