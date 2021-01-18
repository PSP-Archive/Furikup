
#ifndef PSPPHONE_CODEC_H
#define PSPPHONE_CODEC_H

int getAudioPort(void);
int getVideoPort(void);

char *ipaddr(const StunAddress4 *addr);

void createLocalSdp(char *localSdp, sdp_message_t *remoteSdp);

#endif
