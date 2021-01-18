 /*
  The oRTP library is an RTP (Realtime Transport Protocol - rfc3550) stack..
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
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#endif

#include <pspkernel.h>
#include <psputility_netmodules.h>
#include <pspctrl.h>
#include <netinet/in.h>
#include <pspaudio.h>

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

int cond=1;

void stop_handler(int signum)
{
	cond=0;
}

void ssrc_cb(RtpSession *session)
{
	printf("hey, the ssrc has changed !\n");
}

static char *help="usage: rtprecv  filename loc_port [--format format] [--soundcard] [--noadapt] [--with-jitter <milliseconds>]\n";

#define MULAW 0
#define ALAW 1

#if defined(__hpux) && HAVE_SYS_AUDIO_H

#include <sys/audio.h>

int sound_init(int format)
{
	int fd;
	fd=open("/dev/audio",O_WRONLY);
	if (fd<0){
		perror("Can't open /dev/audio");
		return -1;
	}
	ioctl(fd,AUDIO_RESET,0);
	ioctl(fd,AUDIO_SET_SAMPLE_RATE,8000);
	ioctl(fd,AUDIO_SET_CHANNELS,1);
	if (format==MULAW)
		ioctl(fd,AUDIO_SET_DATA_FORMAT,AUDIO_FORMAT_ULAW);
	else ioctl(fd,AUDIO_SET_DATA_FORMAT,AUDIO_FORMAT_ALAW);
	return fd;	
}
#else
int sound_init(int format)
{
	return -1;
}
#endif

static inline int ulaw_to_s16(unsigned char u_val)
{
	int t;

	/* Complement to obtain normal u-law value. */
	u_val = ~u_val;

	/*
	 * Extract and bias the quantization bits. Then
	 * shift up by the segment number and subtract out the bias.
	 */
	t = ((u_val & 0x0f) << 3) + 0x84;
	t <<= (u_val & 0x70) >> 4;

	return ((u_val & 0x80) ? (0x84 - t) : (t - 0x84));
}

void convertAudio(unsigned char *buffer, short *outbuffer)
{
	int i;
	short temp;

	for(i=0; i<160; i++)
	{
		temp = ulaw_to_s16(buffer[i]);
		outbuffer[i*6] = temp;
		outbuffer[i*6+1] = temp;
		outbuffer[i*6+2] = temp;
		outbuffer[i*6+3] = temp;
		outbuffer[i*6+4] = temp;
		outbuffer[i*6+5] = temp;
	}
}

int main(int argc, char*argv[])
{
	RtpSession *session;
	unsigned char buffer[1024];
	unsigned short outbuffer[1024];
	int err;
	uint32_t ts=0;
	int stream_received=0;
	FILE *outfile;
	int local_port;
	int have_more;
	int i;
	int format=0;
	int soundcard=0;
	int sound_fd=0;
	int jittcomp=40;
	bool_t adapt=TRUE;

	sceUtilityLoadNetModule(PSP_NET_MODULE_COMMON);
	sceUtilityLoadNetModule(PSP_NET_MODULE_INET);

	pspSdkInetInit();
	connect_to_apctl(1);

	pspDebugScreenInit();

	printf("rc=%x\n", kAudioSetFrequency(48000));

#if 0
	/* init the lib */
	if (argc<3){
		printf(help);
		return -1;
	}
	local_port=atoi(argv[2]);
	if (local_port<=0) {
		printf(help);
		return -1;
	}
	for (i=3;i<argc;i++)
	{
		if (strcmp(argv[i],"--noadapt")==0) adapt=FALSE;
		if (strcmp(argv[i],"--format")==0){
			i++;
			if (i<argc){
				if (strcmp(argv[i],"mulaw")==0){
					format=MULAW;
				}else
				if (strcmp(argv[i],"alaw")==0){
					format=ALAW;
				}else{
					printf("Unsupported format %s\n",argv[i]);
					return -1;
				}
			}
		}
		else if (strcmp(argv[i],"--soundcard")==0){
			soundcard=1;
		}
		else if (strcmp(argv[i],"--with-jitter")==0){
			i++;
			if (i<argc){
				jittcomp=atoi(argv[i]);
				printf("Using a jitter buffer of %i milliseconds.\n",jittcomp);
			}
		}
	}
#endif

	local_port = 6760;

	outfile=fopen("host0:/test.wav","wb");
	if (outfile==NULL) {
		perror("Cannot open file for writing");
		return -1;
	}
	
	
	if (soundcard){
		sound_fd=sound_init(format);
	}

	int audio_channel = sceAudioChReserve(0, 960, PSP_AUDIO_FORMAT_MONO);

	ortp_init();
	ortp_scheduler_init();
	ortp_set_log_level_mask(ORTP_DEBUG|ORTP_MESSAGE|ORTP_WARNING|ORTP_ERROR);
	signal(SIGINT,stop_handler);
	session=rtp_session_new(RTP_SESSION_RECVONLY);	
	rtp_session_set_scheduling_mode(session,1);
	rtp_session_set_blocking_mode(session,1);
	rtp_session_set_local_addr(session,"0.0.0.0",local_port);
	rtp_session_set_connected_mode(session,TRUE);
	rtp_session_set_symmetric_rtp(session,TRUE);
	rtp_session_enable_adaptive_jitter_compensation(session,adapt);
	rtp_session_set_jitter_compensation(session,jittcomp);
	rtp_session_set_payload_type(session,0);
	rtp_session_signal_connect(session,"ssrc_changed",(RtpCallback)ssrc_cb,0);
	rtp_session_signal_connect(session,"ssrc_changed",(RtpCallback)rtp_session_reset,0);

	while(cond)
	{
		have_more=1;
		while (have_more){
			err=rtp_session_recv_with_ts(session,buffer,160,ts,&have_more);
			if (err>0) stream_received=1;
			/* this is to avoid to write to disk some silence before the first RTP packet is returned*/	
			if ((stream_received) && (err>0)) {
				size_t ret = fwrite(buffer,1,err,outfile);

				convertAudio(buffer, outbuffer);

				sceAudioOutputBlocking(audio_channel, PSP_AUDIO_VOLUME_MAX/2, outbuffer);
			}
		}
		ts+=160;
		//ortp_message("Receiving packet.");
	}
	
	rtp_session_destroy(session);
	ortp_exit();
	
	ortp_global_stats_display();
	
	return 0;
}
