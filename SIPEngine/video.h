
#ifndef VIDEO_H
#define VIDEO_H

void initVideo(void);
int videoAvailable(void);
void rtpVideoSetup(int tid, int incoming);
void rtpVideoStop(void);

#endif
