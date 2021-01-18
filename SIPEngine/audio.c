#include <string.h>
#include <stdlib.h>
#include <pspkernel.h>
#include <pspaudio.h>
#include <pspiofilemgr.h>
#include <ortp/ortp.h>
#include <ortp/stun.h>
#include <osipparser2/sdp_message.h>
#include <eXosip2/eXosip.h>

#include "pspmic.h"
#include "audio.h"
#include "codec.h"
#include "pspusbcam.h"
#include "sound_conv.h"
#include "sound_resample.h"
#include "config.h"
#include "sipengineif.h"

#define WAV_HEADER_SIZE 0x2c

static SceUID sendThid = 0;
static SceUID recvThid = 0;
static SceUID ringbackThid = 0;
static int stopAudio;
static RtpSession *session = 0;
static int audio_channel;
static int audio_channel_ringback;
static u8 work[4096];
static int rtp_payload = 0;
static SceUID inputFile = -1;
static SceUID ringbackfile = -1;
static int ringback = 0;

int rtpAudioRecv(SceSize args, void *argp);
int rtpAudioSend(SceSize args, void *argp);

struct wavheader {
	char           chunkID[4];
	unsigned long  chunkSize;
	char           format[4];
	char           chunk1ID[4];
	unsigned long  chunk1size;
	unsigned short audioFormat;
	unsigned short numChannels;
	unsigned long  sampleRate;
	unsigned long  byteRate;
	unsigned short blockAlign;
	unsigned short bitsPerSample;
	char           chunk2ID[4];
	unsigned long  chunk2size;
};

int checkWavFormat(SceUID inputFile,
									 unsigned long freq,
									 int bitsPerSample,
									 int numChannels)
{
	int rc = 0;
	
	struct wavheader lheader;
	
	int lsize = sceIoRead(inputFile, &lheader, sizeof(lheader));
	if (lsize < sizeof(lheader))
	{
		InfoMessage("Failed to read wav header: 0x%08X", lsize);
		rc = -1;
	}
	else
	{
		if (lheader.bitsPerSample != bitsPerSample)
		{
			InfoMessage("Wrong bits per sample: %d", lheader.bitsPerSample);
			rc = -2;
		}
		if (lheader.sampleRate != freq)
		{
			InfoMessage("Wrong sample rate: %d", lheader.sampleRate);
			rc = -3;
		}
		if (lheader.numChannels != numChannels)
		{
			InfoMessage("Wrong number of channels: %d", lheader.numChannels);
			rc = -3;
		}
	}	
	
	return rc;
}

int initAudio(void)
{
	int result = 0;

	if (config_use_usb())
	{
		if (config_get_use_video())
		{
			PspUsbCamSetupMicParam micparam;

			memset(&micparam, 0, sizeof(micparam));
			micparam.size = sizeof(micparam);
			micparam.gain = 20;
			micparam.frequency = 44100;

			result = sceUsbCamSetupMic(&micparam, work, sizeof(work));
			if (result < 0)
			{
				ErrorMessage("Error 0x%08X in sceUsbCamSetupMic.\n", result);
			}
			
			result = sceUsbCamStartMic();
			if (result < 0)
			{
				ErrorMessage("Error 0x%08X starting mic.\n", result);
			}
		}
		else
		{
			// Setup USB
			result = sceUsbMicInputInit(0, 4096, 0);
			if (result < 0)
			{
				ErrorMessage("Error 0x%08X starting mic.\n", result);
			}
		}
	}
	else if (config_use_headset())
	{
		// Setup for Socom headset
		result = sceAudioInputInit(0, 4096, 0);
		if (result < 0)
		{
			ErrorMessage("Error 0x%08X starting mic.\n", result);
		}
	}
	else if (config_use_inputfile())
	{
		// setup reading from input file
		result = sceIoOpen("audio.wav", PSP_O_RDONLY, 0777);
		if (result < 0)
		{
			ErrorMessage("Error 0x%08X reading audio.wav file", result);
			inputFile = -1;
		}
		else
		{
			inputFile = result;
			
			if (checkWavFormat(inputFile, 44100, 16, 1))
			{
				ErrorMessage("Error: audio.wav must be 44.1kHz, 16 bit mono");
				sceKernelDelayThread(2 * 1000 * 1000);
			}
			sceIoLseek32(inputFile, WAV_HEADER_SIZE, SEEK_SET);
		}
	}

	ResampleAudioInit();

	audio_channel = sceAudioChReserve(PSP_AUDIO_NEXT_CHANNEL,
																		960,
									                  PSP_AUDIO_FORMAT_MONO);
	
	audio_channel_ringback = sceAudioChReserve(PSP_AUDIO_NEXT_CHANNEL,
										    								 1024,
									                       PSP_AUDIO_FORMAT_MONO);
	
	ringbackfile = sceIoOpen("ringback.wav", PSP_O_RDONLY, 0777);
	if (ringbackfile < 0)
	{
		InfoMessage("Error 0x%08X opening ringback.wav file", ringbackfile);
	}

	return result;
}

void rtpAudioSetup(int tid, int incoming)
{
	sdp_message_t *rem_sdp;
	sdp_media_t *rem_media;
	sdp_message_t *loc_sdp;
	sdp_media_t *loc_media;
	sdp_connection_t *rem_con;
	char *payload;

	rem_sdp = eXosip_get_remote_sdp_from_tid(tid);
	rem_con = eXosip_get_audio_connection(rem_sdp);
	rem_media = eXosip_get_audio_media (rem_sdp);

	loc_sdp = eXosip_get_remote_sdp_from_tid(tid);
	loc_media = eXosip_get_audio_media (loc_sdp);

	if(incoming)
	{
		payload = osip_list_get (&loc_media->m_payloads, 0);
	}
	else
	{
		payload = osip_list_get (&rem_media->m_payloads, 0);
	}

	rtp_payload = atoi(payload);

	session=rtp_session_new(RTP_SESSION_SENDRECV);	
	rtp_session_set_scheduling_mode(session,1);
	rtp_session_set_blocking_mode(session,1);
	rtp_session_set_connected_mode(session,TRUE);
	rtp_session_set_symmetric_rtp(session, TRUE);
	rtp_session_enable_adaptive_jitter_compensation(session,TRUE);
	rtp_session_set_jitter_compensation(session,TRUE);
	rtp_session_signal_connect(session,"ssrc_changed",(RtpCallback)rtp_session_reset,0);

	rtp_session_set_local_addr(session, "0.0.0.0", getAudioPort());
	rtp_session_set_remote_addr(session, rem_con->c_addr, atoi(rem_media->m_port));

	rtp_session_set_payload_type(session, atoi(payload));

	// Now to setup and two audio threads
	recvThid = sceKernelCreateThread("AudioRecv", rtpAudioRecv, 0x10, 0x10000, 0, NULL);
	sceKernelStartThread(recvThid, 0, 0);

	sendThid = sceKernelCreateThread("AudioSend", rtpAudioSend, 0x10, 0x10000, 0, NULL);
	sceKernelStartThread(sendThid, 0, 0);

	stopAudio = 0;
}

void rtpAudioStop(void)
{
	sceKernelTerminateDeleteThread(sendThid);
	sceKernelTerminateDeleteThread(recvThid);

	rtp_session_destroy(session);
}

#define AUDIO_SCALE_FACTOR 6.04

int rtpAudioRecv(SceSize args, void *argp)
{
	int err;
	int ts = 0;
	int curpos, curbufidx;
	int have_more = 1;
	unsigned char audioRecvBuffer[1024];
	short audioOutputBuffer[1024];
	
	memset(audioRecvBuffer, 0, 1024);
	
	int (*scale_fn)(unsigned char);

	if (rtp_payload == 0)
	{
		scale_fn = ulaw_to_s16;
	}
	else
	{
		scale_fn = alaw_to_s16;
	}
	
	while (!stopAudio)
	{
		err = rtp_session_recv_with_ts(session, audioRecvBuffer, 160, ts, &have_more);
		if (err>0)
		{
			// Convert from 8khz to 48khz
			float startval, endval, step = 0, val = 0;
			
			for(curpos = 0; curpos < 960; curpos++)
			{
				if (curpos % 6 == 0)
				{
					curbufidx = curpos/6.04;

					// refresh the interpolation constants
					startval = scale_fn(audioRecvBuffer[curbufidx++]);
					endval = scale_fn(audioRecvBuffer[curbufidx]);
					step = (endval - startval) / 6.0;  // twice the real value for fixed-point maths
					val = startval;
				}
				else
				{
					val += step;
				}
				
				audioOutputBuffer[curpos] = val;
			}

			sceAudioOutputBlocking(audio_channel, PSP_AUDIO_VOLUME_MAX, audioOutputBuffer);
		}
		ts+=160;
	}
	
	return ts;
}

// Must be a multiple of 64
#define BUFSIZE 4096

short buffer[BUFSIZE];

int rtpAudioSend(SceSize args, void *argp)
{
	int value;
	unsigned char audioSendBuffer[160];
	int ts = 0;
	int i, j;
	int result = 0;
	int first = 0;
	int sent = 0;

	while(!stopAudio)
	{
		if (config_use_usb())
		{
			if (config_get_use_video())
			{
				if ((sceUsbCamPollReadMicEnd() > 0) || (ts == 0))
				{
					result = sceUsbCamReadMic((u8*)buffer, sizeof(buffer));
				}
			}
			else
			{
				if ((sceUsbMicPollInputEnd() == 0) || (ts == 0))
				{
					result = sceUsbMicInput(BUFSIZE, 44100, (unsigned short *)buffer);
				}
			}
		} 
		else if (config_use_headset())
		{
			if ((sceAudioPollInputEnd() == 0) || (ts == 0))
			{
				result = sceAudioInput(BUFSIZE, 44100, buffer);
			}
		}
		else if (config_use_inputfile())
		{
			if (inputFile == -1)
			{
				memset(buffer, 0, sizeof(buffer));
			}
			else
			{
				if(sent % BUFSIZE >= (BUFSIZE-882))
				{
					sceIoRead(inputFile, buffer, sizeof(buffer));
				}
			}
			result = 1;
		}
		
		if (first)
		{
			sceKernelDelayThread(20*1024);
			first = 0;
		}

		if (result >= 0)
		{
			for(i=0; i<160; i++)
			{
				value = 0;

				// Leaving out the averaging for now, need to add back in later
				for(j=0; j<5; j++)
				{
					value += buffer[((int)(i*5.5) + sent + j) % BUFSIZE];
				}
				value /= 5;

				if (rtp_payload == 0)
				{
					audioSendBuffer[i] = s16_to_ulaw(value);
				}
				else
				{
					audioSendBuffer[i] = s16_to_alaw(value);
				}
			}

			sent += 882;
		}
		else
		{
			if (result < 0)
			{
				InfoMessage("Error 0x%08X reading mic.\n", result);
			}

			memset(audioSendBuffer, 0, 160);
		}

		rtp_session_send_with_ts(session, audioSendBuffer, 160, ts);
		ts += 160;
	}
	
	return ts;
}

unsigned short ringbackbuffer[1024];
int playRingbackThread(SceSize args, void *argp)
{
	while (ringback)
	{
		sceIoLseek32(ringbackfile, WAV_HEADER_SIZE, SEEK_SET);
		int lread;
		while ((lread = sceIoRead(ringbackfile, ringbackbuffer, 2048)) && ringback)
		{
			sceAudioOutputBlocking(audio_channel_ringback, PSP_AUDIO_VOLUME_MAX, ringbackbuffer);
		}
		
		if (ringback)
		{
			sceKernelDelayThread(2 * 1000 * 1000);
		}
	}

	sceKernelExitDeleteThread(0);
	return 0;
}

void playRingback(void)
{
	ringback = 1;
	if (ringbackfile >= 0)
	{
		ringbackThid = sceKernelCreateThread("AudioRingback", playRingbackThread, 0x18, 0x10000, 0, NULL);
		sceKernelStartThread(ringbackThid, 0, 0);
	}
}

void stopRingback(void)
{
	ringback = 0;
}
