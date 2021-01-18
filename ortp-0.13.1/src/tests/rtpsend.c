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

static char *help="usage: rtpsend	filename dest_ip4addr dest_port [ --with-clockslide <value> ] [ --with-jitter <milliseconds>]\n";

int main(int argc, char *argv[])
{
	sceUtilityLoadNetModule(PSP_NET_MODULE_COMMON);
	sceUtilityLoadNetModule(PSP_NET_MODULE_INET);

	pspSdkInetInit();
	connect_to_apctl(1);

	RtpSession *session;
	unsigned char buffer[160];
	int i;
	FILE *infile;
	char *ssrc;
	uint32_t user_ts=0;
	int clockslide=0;
	int jitter=0;

#if 0
	if (argc<4){
		printf(help);
		return -1;
	}
	for(i=4;i<argc;i++){
		if (strcmp(argv[i],"--with-clockslide")==0){
			i++;
			if (i>=argc) {
				printf(help);
				return -1;
			}
			clockslide=atoi(argv[i]);
			ortp_message("Using clockslide of %i milisecond every 50 packets.",clockslide);
		}else if (strcmp(argv[i],"--with-jitter")==0){
			ortp_message("Jitter will be added to outgoing stream.");
			i++;
			if (i>=argc) {
				printf(help);
				return -1;
			}
			jitter=atoi(argv[i]);
		}
	}
#endif

	ortp_init();
	ortp_scheduler_init();
	ortp_set_log_level_mask(ORTP_MESSAGE|ORTP_WARNING|ORTP_ERROR);
	session=rtp_session_new(RTP_SESSION_SENDONLY);	
	rtp_session_set_scheduling_mode(session,1);
	rtp_session_set_blocking_mode(session,1);
	rtp_session_set_connected_mode(session,TRUE);
	rtp_session_set_remote_addr(session,"192.168.0.4",6760);
	rtp_session_set_payload_type(session,0);
	
	ssrc=getenv("SSRC");
	if (ssrc!=NULL) {
		printf("using SSRC=%i.\n",atoi(ssrc));
		rtp_session_set_ssrc(session,atoi(ssrc));
	}
		
//#ifndef _WIN32
//	infile=fopen("ms0:/test.wav","r");
//#else
	infile=fopen("ms0:/test.wav","rb");
//#endif

	if (infile==NULL) {
		perror("Cannot open file");
		return -1;
	}

//	signal(SIGINT,stophandler);
	while( ((i=fread(buffer,1,160,infile))>0) && (runcond) )
	{
		rtp_session_send_with_ts(session,buffer,i,user_ts);
		user_ts+=160;
		if (clockslide!=0 && user_ts%(160*50)==0){
			ortp_message("Clock sliding of %i miliseconds now",clockslide);
			rtp_session_make_time_distorsion(session,clockslide);
		}
		/*this will simulate a burst of late packets */
		if (jitter && (user_ts%(8000)==0)) {
			struct timespec pausetime, remtime;
			ortp_message("Simulating late packets now (%i milliseconds)",jitter);
			pausetime.tv_sec=jitter/1000;
			pausetime.tv_nsec=(jitter%1000)*1000000;
			while(nanosleep(&pausetime,&remtime)==-1){
				pausetime=remtime;
			}
		}
	}

	fclose(infile);
	rtp_session_destroy(session);
	ortp_exit();
	ortp_global_stats_display();

	return 0;
}
