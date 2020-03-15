// MT MK3 OM v0.3 [Sir Ababol NES_OM]
// Copyleft 2017, 2018 by The Mojon Twins

// Printer

void draw_tile (void) {
	gp_gen = tsmaps + (rdt << 3);
	sp_PrintAtInv (rdy    , rdx    , *gp_gen ++, *gp_gen ++);
	sp_PrintAtInv (rdy    , rdx + 1, *gp_gen ++, *gp_gen ++);
	sp_PrintAtInv (rdy + 1, rdx    , *gp_gen ++, *gp_gen ++);
	sp_PrintAtInv (rdy + 1, rdx + 1, *gp_gen ++, *gp_gen );
}

void all_sprites_out (void) {
	gpit = SW_SPRITES_ALL; while (gpit-- > rda) { if (spr_on [gpit]) SPRITE_OUT (gpit); }
}

void blackout (void) {
	#asm
		ld bc, 767
		ld hl, 0x5800
		ld de, 0x5801
		xor a
		ld (hl), a
		ldir
	#endasm
}

void unpack_scr (unsigned char res) {
	sp_UpdateNow ();
	blackout ();
	librarian_get_resource (res, (unsigned char *) (0x4000));
}

void frame_ending (unsigned char *s) {
	// Shows ending picture (or not) plus text
	sp_UpdateNow ();
	if (rda) {
		unpack_scr (ENDING_C); 		
	} else {
		CLEAR_RECT (RECT_FULL_SCREEN);
	}	
	rdc = 71; rdx = 2; rdy = 13; p_s (s);
	sp_UpdateNow ();
	wait_button ();	
}
