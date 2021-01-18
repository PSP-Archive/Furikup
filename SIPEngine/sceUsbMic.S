	.set noreorder

#include "pspstub.s"

	STUB_START	"sceUsbMic",0x40090011,0x00070005
	STUB_FUNC	0x06128E42,sceUsbMicPollInputEnd
	STUB_FUNC	0x2E6DCDCD,sceUsbMicInputBlocking
	STUB_FUNC	0x45310F07,sceUsbMicInputInitEx
	STUB_FUNC	0x5F7F368D,sceUsbMicInput
	STUB_FUNC	0x63400E20,sceUsbMicGetInputLength
	STUB_FUNC	0xB8E536EB,sceUsbMicInputInit
	STUB_FUNC	0xF899001C,sceUsbMicWaitInputEnd
	STUB_END
