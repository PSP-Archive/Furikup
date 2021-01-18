
#ifndef PSPUSBMIC_H
#define PSPUSBMIC_H

#define PSP_USBMIC_DRIVERNAME "USBMicDriver"
#define PSP_USBMIC_PIC 0x025B

int sceAudioInputInit(int arg0, int vol, int arg2);
int sceAudioInputBlocking(int length, int sample_rate, void *buf);
int sceAudioInput(int length, int sample_rate, void *buf);
int sceAudioPollInputEnd(void);

int sceUsbMicInputInit(int arg0, int vol, int arg2);
int sceUsbMicInput(int length, int sample_rate, void *buf);
int sceUsbMicPollInputEnd(void);

#endif
