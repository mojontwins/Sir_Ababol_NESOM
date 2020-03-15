// MT MK3 OM v0.3 [Sir Ababol NES_OM]
// Copyleft 2017, 2018 by The Mojon Twins

// Printer

void p_s (unsigned char *s) {
	rdxx = rdx; rdyy = rdy;
	while (*s) {
		rdch = *s ++;
		if (rdch == '/') { rdxx = rdx; rdyy ++; } else {
			DRAW_PATTERN (rdxx ++, rdyy, rdc, rdch - 32);
		}
	}
}

#ifdef SPECCY
	#include "engine/printer_speccy.h"
	#define DRAW_TILE 		draw_tile
	#define DRAW_TILE_UPD	draw_tile
#endif
#ifdef CPC
	#include "engine/printer_cpc.h"
	#define DRAW_TILE 		draw_tile
	#define DRAW_TILE_UPD	draw_tile_upd
#endif

void set_map_tile (void) {
	rdf = (rdy << 4) | rdx;
	scr_buff [rdf] = rdt; scr_attr [rdf] = behs [rdt];
	rdx = SCR_X + (rdx << 1); rdy = SCR_Y + (rdy << 1);
	DRAW_TILE_UPD ();
}

void draw_tile_advance (void) {
	DRAW_TILE (); 
	rdx += 2; 
	if (rdx == MAP_CHARSW + SCR_X) { 
		rdx = SCR_X; 
		rdy += 2; 
		#ifndef MAP_WIDTH_16		
			gpit ++;
		#endif
	}
}

void advance_worm (void) {
	rdd = rdt;

#ifdef MAP_USE_ALT_TILE
	if (rdt == 0 && ALT_TILE_EXPRESSION) rdt = MAP_USE_ALT_TILE;
#endif

	rda = behs [rdt];
#ifdef FLOATY_PUSH_BOXES
	scr_buff [gpit] = (rda & PUSHABLE_BEH) ? FLOATY_PUSH_BOXES_SUBST : rdt;
#else	
	scr_buff [gpit] = rdt; 
#endif	
	scr_attr [gpit] = rda;
	draw_tile_advance (); gpit ++;

	rdt = rdd;
}

void scr_rand (void) {
	// Set random seed
	seed1 [0] = n_pant; seed2 [0] = n_pant + 69; srand ();
}

void draw_scr (void) {
#ifdef CPC
	cpc_ResetTouchedTiles ();
#endif	

	scr_rand ();

	// Find address
	gp_map = map_base_address ();

#ifdef MAP_FORMAT_RLE44
	gpit = 0; rdx = SCR_X; rdy = SCR_Y;
	while (gpit < 160) {
		rdt = *gp_map ++;
		rdct = 1 + (rdt >> 4);
		rdt &= 0x0f;
		while (rdct --) advance_worm ();
	}
#endif

#ifdef MAP_FORMAT_RLE53	
	gpit = 0; rdx = SCR_X; rdy = SCR_Y;
	while (gpit < 160) {
		rdt = *gp_map ++;
		rdct = 1 + (rdt >> 5);
		rdt &= 0x1f;
		while (rdct --) advance_worm ();
	}
#endif

#ifdef MAP_FORMAT_PACKED
	gpit = 0; rdx = SCR_X; rdy = SCR_Y; rde = 1;
	while (gpit < 160) {
		if (rde) {
			rdct = *gp_map ++; rdt = rdct >> 4;
		} else {
			rdt = rdct & 0x0f;
		}
		rde = 1 - rde;
		advance_worm ();
	}
#endif
}

void draw_scr_buffer (void) {
#ifdef CPC
	cpc_ResetTouchedTiles ();
#endif	

	scr_rand ();

	gpit = 0; rdx = SCR_X; rdy = SCR_Y;
	gp_map = scr_buff;
	while (gpit < 160) {
		rdt = scr_buff [gpit ++];
		draw_tile_advance ();
	}

#ifdef CPC
	cpc_ShowTileMap (0);
#endif	
}

void p_t2 (unsigned char x, unsigned char y, unsigned char n) {
	DRAW_PATTERN_UPD (x ++, y, rdc, DIGIT(n/10));
	DRAW_PATTERN_UPD (x   , y, rdc, DIGIT(n%10));
}

#ifdef DEBUG
unsigned char hexd (unsigned char n) {
	if (n < 10) return DIGIT(n);
	return 'A'-10+n-32;
}

void p_hex (unsigned char x, unsigned char y, unsigned char n) {
	DRAW_PATTERN_UPD (x ++, y, 71, hexd(n >> 4));
	DRAW_PATTERN_UPD (x   , y, 71, hexd(n & 0xf));
}
#endif
