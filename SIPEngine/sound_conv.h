
#ifndef SOUND_CONV_H
#define SOUND_CONV_H

unsigned char s16_to_ulaw (int pcm_val);
int ulaw_to_s16 (unsigned char u_val);
unsigned char s16_to_alaw (int pcm_val);
int alaw_to_s16 (unsigned char u_val);

#endif
