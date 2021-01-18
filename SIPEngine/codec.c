
#include <netinet/in.h>
#include <ortp/stun.h>
#include <eXosip2/eXosip.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "codec.h"
#include "config.h"

int audioPort = 0;
int videoPort = 0;
int portCount = 30000;

int getAudioPort(void)
{
	return audioPort;
}

int getVideoPort(void)
{
	return videoPort;
}

void createLocalSdp(char *localSdp, sdp_message_t *remoteSdp)
{
	int fd1, fd2;
	int mapped_port;
	int video_port;
	char addr[128];
	char videooptions[128]; 
	sdp_media_t *rem_media;
	char *payload;
	int jpegSupported;
	int pos = 0;
	int added = 0;
	char audiooptions[128];
	char audiomap[128];

	memset(audiooptions, 0, sizeof(audiooptions));
	memset(audiomap, 0, sizeof(audiomap));
	memset(videooptions, 0, sizeof(videooptions));

	audioPort = portCount;
	portCount += 2;
	videoPort = portCount;
	portCount += 2;

	if (config_get_nat_traversal())
	{
		StunAddress4 dest;
		StunAddress4 mapAddr_rtp;
		StunAddress4 mapAddr_rtcp;

		stunParseServerName(config_get_stun_server(), &dest);
		dest.port = config_get_stun_port();

		stunOpenSocketPair(&dest,
				&mapAddr_rtp,
				&mapAddr_rtcp,
				&fd1, &fd2,
				audioPort, 0,
				1);

		closesocket(fd1);
		closesocket(fd2);

		strncpy(addr, ipaddr(&mapAddr_rtp), 128);
		mapped_port = mapAddr_rtp.port;
	}
	else
	{
		eXosip_guess_localip (AF_INET, addr, 128);
		mapped_port = audioPort;
	}

	sprintf(audiooptions, "m=audio %d RTP/AVP", mapped_port); 

	if (remoteSdp)
	{
		// Check if ALAW & MULAW are both supported
		rem_media = eXosip_get_audio_media (remoteSdp);

		if (rem_media)
		{
			pos = 0;
			payload = osip_list_get (&rem_media->m_payloads, pos++);

			while (payload)
			{
				if (atoi(payload) == 0)
				{
					added = 1;
					strcat(audiooptions, " 0");
					strcat(audiomap, "a=rtpmap:0 PCMU/8000\r\n");
				}
				else if (atoi(payload) == 8)
				{
					added = 1;
					strcat(audiooptions, " 8");				
					strcat(audiomap, "a=rtpmap:8 PCMA/8000\r\n");
				}

				payload = osip_list_get (&rem_media->m_payloads, pos++);
			}
		}

		if (!added)
		{
			// No supported codecs
			sprintf(audiooptions, "m=audio 0 RTP/AVP 0"); 
			strcat(audiomap, "a=rtpmap:0 PCMU/8000\r\n");
		}

		// Check if JPEG video is supported
		rem_media = eXosip_get_video_media (remoteSdp);

		if (rem_media)
		{
			pos = 0;
			payload = osip_list_get (&rem_media->m_payloads, pos++);

			while (payload)
			{
				if (atoi(payload) == 26)
				{
					jpegSupported = 1;
				}

				payload = osip_list_get (&rem_media->m_payloads, pos++);
			}

			// As we had a video code included, ensure that we reject it
			if (!jpegSupported)
			{
				sprintf(videooptions, "m=video 0 RTP/AVP 26\r\n");
			}
		}
	}
	else
	{
		strcat(audiooptions, " 0 8 101");
		strcat(audiomap, "a=rtpmap:0 PCMU/8000\r\n");
		strcat(audiomap, "a=rtpmap:8 PCMA/8000\r\n");
		strcat(audiomap, "a=rtpmap:101 telephone-event/8000\r\n");
	}

	if(config_get_use_video() && ((!remoteSdp) || (jpegSupported)))
	{
		if (config_get_nat_traversal())
		{
			StunAddress4 dest;
			StunAddress4 mapAddr_rtp;
			StunAddress4 mapAddr_rtcp;

			stunParseServerName(config_get_stun_server(), &dest);
			dest.port = config_get_stun_port();

			stunOpenSocketPair(&dest,
					&mapAddr_rtp,
					&mapAddr_rtcp,
					&fd1, &fd2,
					videoPort, 0,
					1);

			closesocket(fd1);
			closesocket(fd2);

			video_port = mapAddr_rtp.port;		
		}
		else
		{
			eXosip_guess_localip (AF_INET, addr, 128);
			video_port = videoPort;
		}

		sprintf(videooptions, "m=video %d RTP/AVP 26\r\n", video_port);
	}

	// Need to add in parsing of the remote SDP rather than just assuming
	snprintf (localSdp, 
			1024,
			"v=0\r\n"
			"o=- 200 200 IN IP4 %s\r\n"
			"s=SIP Phone\r\n"
			"c=IN IP4 %s\r\n"
			"t=0 0\r\n"
			"%s\r\n"
			"%s"
			"%s"
			"a=ptime:20\r\n",
			addr, addr, audiooptions, videooptions, audiomap);

	return;
}

char *ipaddr(const StunAddress4 *addr)
{
   struct in_addr inaddr;
   inaddr.s_addr = htonl(addr->addr);
   return (char *)inet_ntoa(inaddr);
}
