// MTEZX MK3
// Copyleft 2017 by The Mojon Twins

// library

extern const unsigned char title_c [0];
#asm
	._title_c
		BINARY "../ports/cpc/bin/title.c.bin"
#endasm

extern const unsigned char frame_c [0];
#asm
	._frame_c
		BINARY "../ports/cpc/bin/frame.c.bin"
#endasm

extern const unsigned char ending_c [0];
#asm
	._ending_c
		BINARY "../ports/cpc/bin/ending.c.bin"
#endasm

extern const unsigned char m0_c [0];
#asm
	._m0_c
		BINARY "../ports/cpc/bin/m0.c.bin"
#endasm

extern const unsigned char m1_c [0];
#asm
	._m1_c
		BINARY "../ports/cpc/bin/m1.c.bin"
#endasm

extern const unsigned char m2_c [0];
#asm
	._m2_c
		BINARY "../ports/cpc/bin/m2.c.bin"
#endasm

const unsigned char * library [] = {
	title_c, 
	frame_c, 
	ending_c, 
	m0_c, 
	m1_c, 
	m2_c
};

#define TITLE_C 0x00
#define FRAME_C 0x01
#define ENDING_C 0x02
#define M0_C 0x03
#define M1_C 0x04
#define M2_C 0x05

