	.set noreorder

#include "pspstub.s"

	STUB_START "SIPEngine",0x00090000,0x00030005
	STUB_FUNC  0x4516ED61,SIPEngineInitialize
	STUB_FUNC  0xD1793878,SIPEngineDoEvent
	STUB_FUNC  0x9A79FEFC,SIPEngineGetBuild
	STUB_END
