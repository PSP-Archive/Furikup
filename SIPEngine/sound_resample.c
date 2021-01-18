
#include "sound_resample.h"
#include "sound_conv.h"

#include "FirAlgs.c"

float *tempIn;
float *tempOut;

#define NTAPS 8
#define IMP_SIZE (3 * NTAPS)

static const SAMPLE h[NTAPS] = 
{
	-0.192761875,
	 0.121943383,
	-2.085947762,
	 0.635617843,
	 0.635617843,
	-2.085947762,
	 0.121943383,
	-0.192761875
};

static SAMPLE h2[2 * NTAPS] = {0};
static SAMPLE z[2 * NTAPS] = {0};
int state = 0;

int ResampleAudioInit(void)
{
	int i;

	for (i = 0; i < NTAPS; i++) 
	{
		h2[i] = h2[i + NTAPS] = h[i];
	}

	return 0;
}

void ResampleAudio(short *inBuffer, int inLen, unsigned char *outBuffer, int outLen, int rtp_payload)
{
	short output;
	int i;
	float factor = (float)inLen/(float)outLen;

	for(i=0; i<outLen; i++)
	{
		output = fir_double_h(inBuffer[(int)(i*factor)], NTAPS, h2, z, &state);

		if (rtp_payload == 0)
		{
			outBuffer[i] = s16_to_ulaw(output);
		}
		else
		{
			outBuffer[i] = s16_to_alaw(output);
		}
	}
}
