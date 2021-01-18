
#include <pspkernel.h>
#include <pspaudio_kernel.h>

PSP_MODULE_INFO("AudioFreq", 0x1000, 1, 0);
PSP_MAIN_THREAD_ATTR(0);

int module_start(void)
{
  if(sceAudioSetFrequency(48000) == 0x8002013A)
  {
    sceAudioSetFrequency371(48000);
  }

  return 1;
}

