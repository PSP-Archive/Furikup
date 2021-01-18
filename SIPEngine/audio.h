
#ifndef PSPPHONE_AUDIO_H
#define PSPPHONE_AUDIO_H

int initAudio(void);
void rtpAudioSetup(int tid, int incoming);
void rtpAudioStop(void);
void playRingback(void);
void stopRingback(void);

#endif
