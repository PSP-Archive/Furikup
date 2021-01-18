	.set noreorder

#include "pspstub.s"

	STUB_START "PSPEngine",0x40090000,0x00020005
	STUB_FUNC  0x16EE74AE,PSPEngineInitialize
	STUB_FUNC  0xA4730833,PSPEngineDoEvent
	STUB_END
