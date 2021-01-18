
#ifndef PSPPHONE_CALL_API_H
#define PSPPHONE_CALL_API_H

int setupCallThread(void);

int makeCall(char *user);
void answerCall(void);
void hangupCall(void);

void disconnectSipServer(void);

void registerCallbackProc(void *proc);

#endif
