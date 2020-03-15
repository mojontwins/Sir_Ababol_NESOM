// MT MK3 OM v0.3 [Sir Ababol NES_OM]
// Copyleft 2017, 2018 by The Mojon Twins

// Printer

void draw_tile (void) {
	gp_gen = tsmaps + (rdt << 2);
	cpc_SetTile (rdx    , rdy    , *gp_gen ++);
	cpc_SetTile (rdx + 1, rdy    , *gp_gen ++);
	cpc_SetTile (rdx    , rdy + 1, *gp_gen ++);
	cpc_SetTile (rdx + 1, rdy + 1, *gp_gen);
}

void draw_tile_upd (void) {
	gp_gen = tsmaps + (rdt << 2);
	cpc_SetTouchTileXY (rdx    , rdy    , *gp_gen ++);
	cpc_SetTouchTileXY (rdx + 1, rdy    , *gp_gen ++);
	cpc_SetTouchTileXY (rdx    , rdy + 1, *gp_gen ++);
	cpc_SetTouchTileXY (rdx + 1, rdy + 1, *gp_gen);
}

void all_sprites_out (void) {
	gpit = SW_SPRITES_ALL; while (gpit-- > rda) { if (spr_on [gpit]) SPRITE_OUT (gpit); }
}

void blackout (void) {

}

void unpack_scr (unsigned char res) {
	librarian_get_resource (res, (unsigned char *) (BASE_SUPERBUFF));
}

void cpc_clear_rect (unsigned char which) {
	if (which) {
		rdy = 20; while (rdy --) {
			rdx = 30; while (rdx --) {
				cpc_SetTile (SCR_X + rdx, SCR_Y + rdy, 0);
			}
		}
	} else {
		gpint = 768; while (gpint --) {
			nametable [gpint] = 0;
		}
	}
}

void cpc_screen_update (void) {
#ifdef TALL_PLAYER
	gpit = SW_SPRITES_ALL; while (gpit -- > 1) {
		cpc_PutSpTileMap8x16 ((int) (&sp_sw [gpit]));
	}
	if (sp_sw [0].cy > 176) {
		sp_sw [0].cy += 8;
		sp_sw [0].sp0 += 32;
		cpc_PutSpTileMap8x16 ((int) (&sp_sw [0]));
		rda = 1;
	} else {
		cpc_PutSpTileMap8x24 ((int) (&sp_sw [0]));
		rda = 0;
	}
#else
	gpit = SW_SPRITES_ALL; while (gpit --) {
		cpc_PutSpTileMap8x16 ((int) (&sp_sw [gpit]));
	}
#endif

	cpc_UpdScr ();

#ifdef TALL_PLAYER
	gpit = SW_SPRITES_ALL; while (gpit -- > 1) {
		cpc_PutTrSp8x16TileMap2b ((int) (&sp_sw [gpit]));
	}
	if (rda) cpc_PutTrSp8x16TileMap2b ((int) (&sp_sw [gpit]));
	else cpc_PutTrSp8x24TileMap2b ((int) (&sp_sw [0]));
#else
	gpit = SW_SPRITES_ALL; while (gpit --) {
		cpc_PutTrSp8x16TileMap2b ((int) (&sp_sw [gpit]));
	}
#endif

	cpc_ShowTouchedTiles ();
	cpc_ResetTouchedTiles ();
}

void cpc_show_updated (void) {
	cpc_UpdScr ();
	cpc_ShowTouchedTiles ();
	cpc_ResetTouchedTiles ();
}

void p_s_upd (unsigned char *s) {
	rdxx = rdx; rdyy = rdy;
	while (*s) {
		rdch = *s ++;
		if (rdch == '/') { rdxx = rdx; rdyy ++; } else {
			cpc_SetTouchTileXY (rdxx ++, rdyy, rdch - 32);
		}
	}
}

/*
void frame_ending (unsigned char *s) {
	// Shows ending picture (or not) plus text
	if (rda) {
		unpack_scr (ENDING_C); 
		cpc_ShowTileMap (1);
	} else {
		CLEAR_RECT (RECT_FULL_SCREEN);
		SCREEN_UPDATE_NO_SPRITES;
	}	
	cpc_ResetTouchedTiles ();
	rdc = 71; rdx = 2; rdy = 13; p_s_upd (s);
	cpc_show_updated ();
	wait_button ();	
}
*/
