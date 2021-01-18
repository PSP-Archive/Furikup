
#ifndef SOUND_RESAMPLE_H
#define SOUND_RESAMPLE_H

int ResampleAudioInit(void);

void ResampleAudio(short *inBuffer, int inLen, 
				  unsigned char *outBuffer, int outLen, 
				  int rtp_payload);

#endif
