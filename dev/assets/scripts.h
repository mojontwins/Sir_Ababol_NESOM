// MT MK3 OM v0.3 [Sir Ababol NES_OM]
// Copyleft 2017, 2018 by The Mojon Twins

// Scripts

extern unsigned char scripts [0];
#asm
#ifdef SPECCY
	._scripts
		BINARY "../ports/zx/bin/scripts.bin"
#endif
#ifdef CPC
	._scripts
		BINARY "../ports/cpc/bin-b/scripts.bin"		
#endif		
#endasm
