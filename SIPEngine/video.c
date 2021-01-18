#include <stdlib.h>
#include <string.h>
#include <pspkernel.h>
#include <pspaudio.h>
#include <ortp/ortp.h>
#include <ortp/stun.h>
#include <osipparser2/sdp_message.h>
#include <eXosip2/eXosip.h>

#include "video.h"
#include "codec.h"
#include "pspusbcam.h"

static SceUID sendThid = 0;
static SceUID recvThid = 0;
static int stopVideo = 1;
static RtpSession *session = 0;
static int isVidAvailable = 0;

int rtpVideoRecv(SceSize args, void *argp);
int rtpVideoSend(SceSize args, void *argp);

#define MAX_VIDEO_FRAME_SIZE	(32*1024)

static u8  outbuffer[MAX_VIDEO_FRAME_SIZE] __attribute__((aligned(64)));
static u8  inbuffer[MAX_VIDEO_FRAME_SIZE] __attribute__((aligned(64)));
static u8  work[68*1024] __attribute__((aligned(64)));

void initVideo(void)
{
	PspUsbCamSetupVideoParam videoparam;
	int result;

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
		return;
	}

	sceUsbCamAutoImageReverseSW(1);

	result = sceUsbCamStartVideo();	
	if (result < 0)
	{
		printf("Error 0x%08X in sceUsbCamStartVideo.\n", result);
		return;
	}

	isVidAvailable = 1;
}

int videoAvailable(void)
{
	return isVidAvailable;
}

void rtpVideoSetup(int tid, int incoming)
{
	sdp_message_t *rem_sdp;
	sdp_media_t *rem_media;
	sdp_message_t *loc_sdp;
	sdp_media_t *loc_media;
	sdp_connection_t *rem_con;
	char *payload;

	if (!videoAvailable())
	{
		return;
	}

	rem_sdp = eXosip_get_remote_sdp_from_tid(tid);
	rem_con = eXosip_get_video_connection(rem_sdp);
	rem_media = eXosip_get_video_media (rem_sdp);

	loc_sdp = eXosip_get_remote_sdp_from_tid(tid);
	loc_media = eXosip_get_video_media (loc_sdp);

	if(!loc_media && !rem_media)
	{
		return;
	}

	if(incoming)
	{
		payload = osip_list_get (&loc_media->m_payloads, 0);
	}
	else
	{
		payload = osip_list_get (&rem_media->m_payloads, 0);
	}

	// We only support profile 26 (MJPEG) and if the other client returns 0
	// for the port then it does not support the video format.
	if ((atoi(payload) != 26) || (atoi(rem_media->m_port) == 0))
	{
		return;
	}

	session=rtp_session_new(RTP_SESSION_SENDRECV);	
	rtp_session_set_scheduling_mode(session,1);
	rtp_session_set_blocking_mode(session,1);
	rtp_session_set_connected_mode(session,TRUE);
	rtp_session_set_symmetric_rtp(session, TRUE);
	rtp_session_enable_adaptive_jitter_compensation(session,TRUE);
	rtp_session_set_jitter_compensation(session,TRUE);
	rtp_session_signal_connect(session,"ssrc_changed",(RtpCallback)rtp_session_reset,0);

	rtp_session_set_local_addr(session, "0.0.0.0", getVideoPort());
	rtp_session_set_remote_addr(session, rem_con->c_addr, atoi(rem_media->m_port));

	rtp_session_set_payload_type(session, atoi(payload));

	// Now to setup and two audio threads
	recvThid = sceKernelCreateThread("VideoRecv", rtpVideoRecv, 0x18, 0x10000, 0, NULL);
	sceKernelStartThread(recvThid, 0, 0);

	sendThid = sceKernelCreateThread("AudioSend", rtpVideoSend, 0x18, 0x10000, 0, NULL);
	sceKernelStartThread(sendThid, 0, 0);

	stopVideo = 0;
}

void rtpVideoStop(void)
{
	if(!stopVideo)
	{
		sceKernelTerminateDeleteThread(sendThid);
		sceKernelTerminateDeleteThread(recvThid);

		stopVideo = 1;

		rtp_session_destroy(session);
	}
}

int rtpVideoRecv(SceSize args, void *argp)
{
	int ts = 0;
	int err = 0;
	int stream_received;
	int have_more;

	while(!stopVideo)
	{
		have_more = 0;

		err=rtp_session_recv_with_ts(session,inbuffer,sizeof(inbuffer),ts,&have_more);
		if (err>0) stream_received=1;
		/* this is to avoid to write to disk some silence before the first RTP packet is returned*/	
		if ((stream_received) && (err>0)) 
		{
#if 0
			result = sceJpegDecodeMJpeg(inbuffer, err, framebuffer, 0);
			if (result < 0)
			{
				printf("Error 0x%08X decoding mjpeg data.\n", result);
				continue;
			}
#endif
		}

		ts+=6000;
	}
	
	return err;
}

int rtpVideoSend(SceSize args, void *argp)
{
	int result = 0;
	int user_ts = 0;

	while(!stopVideo)
	{
		result = sceUsbCamReadVideoFrameBlocking(outbuffer, MAX_VIDEO_FRAME_SIZE);
		if (result > 0)
		{
			rtp_session_send_with_ts(session, outbuffer, result, user_ts);

			user_ts += 6000;
		}
	}
	
	return result;
}
