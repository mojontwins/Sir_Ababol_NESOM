// MT MK3 OM v0.3 [Sir Ababol NES_OM]
// Copyleft 2017, 2018 by The Mojon Twins

// Game functions

#ifdef SCRIPTING_ON
void game_run_fire_script (void) {
	run_script (2 * MAX_PANTS + 2);		// Press fire in any room.
	run_script (n_pant + n_pant + 1);		// Press fire in current room.
}
#endif

void game_shutdown_sprites (void) {
	gpit = SW_SPRITES_ALL; while (gpit --) spr_on [gpit] = 0;
}

void game_init (void) {

#if defined(ENEMIES_CAN_DIE) && defined(PERSISTENT_DEATHS)
	enems_persistent_deaths_init ();
#endif	

#ifdef PERSISTENT_ENEMIES
	persistent_enems_load ();
#endif

#ifndef DISABLE_HOTSPOTS
	hotspots_ini ();
#endif

#ifdef HOTSPOT_TYPE_KEY
	bolts_load ();
#endif	

	n_pant = c_level [PLAYER_SCR_INI]; // n_pant=4;prx = 224; px=prx<<4;

	player_init ();

	pkeys = pobjs = 0;
	on_pant = oplife = opobjs = opkeys = 0xff;

#ifdef HOTSPOT_TYPE_STAR
	opstars = 0xff;
#endif	

#ifdef ENABLE_TILE_GET
	optile_get_ctr = 0xff;
#endif	
	max_hotspots_type_1 = 1;	// This works for Ninjajar.

	first_time = 1;
#ifdef SPECCY
	unpack_scr (FRAME_C);
	rdc = 15; rdx = 12; rdy = 0; p_s ("NINJAJAR");
	rdy = 23; rdx = 21; p_s ("CARRY:");
#endif
#ifdef CPC
	librarian_get_resource (FRAME_C, nametable);
#endif	
}

void game_prepare_screen (void) {
	draw_scr ();

#ifdef HOTSPOT_TYPE_KEY
	bolts_update_screen ();
#endif
	
#ifndef DISABLE_HOTSPOTS	
	hotspots_load ();
#endif

	if (first_time) first_time = 0; else {
#ifdef PERSISTENT_ENEMIES
		persistent_update ();
#endif
	}

#ifdef BREAKABLE_WALLS
	breakable_init ();
#endif

#ifdef FLOATY_PUSH_BOXES
	fpb_init ();
#endif

	enems_load ();

#ifdef ENABLE_HITTER
	hitter_frame = 0;
#endif

#ifdef ENABLE_COCOS
	simplecoco_init ();
#endif

	enems_do ();

#ifdef SCRIPTING_ON
	f_zone_ac = 0;
	fzx1 = fzx2 = fzy1 = fzy2 = 0;
	run_script (2 * MAX_PANTS + 1);		// Entering any script
	run_script (n_pant + n_pant);			// Entering this room script
#endif	

#ifdef CPC
	cpc_ResetTouchedTiles ();
	cpc_ShowTileMap (0);
#endif	
}

void game_loop (void) {
#ifdef CPC
	cpc_ResetTouchedTiles ();
#endif	
	hud_update ();
#ifdef CPC
	cpc_ShowTouchedTiles ();
	cpc_ResetTouchedTiles ();
#endif

	// Entering Game
	#ifdef SCRIPTING_ON
	#ifdef CLEAR_FLAGS
		msc_clear_flags ();
	#endif
		script_result = 0;
		// Entering game script
		run_script (2 * MAX_PANTS);
	#endif

	do_game = 1; pkilled = 0;
	MUSIC_PLAY (M1_C);

	while (do_game) {
		#include "engine/mainloop/flick_screen.h"

		half_life = 1 - half_life;
		hl_proc = half_life;
		frame_counter ++;

#ifdef SPECCY
		pad0 = CONTROLLER_READ;
#endif		

		pgotten = pgtmx = pgtmy = 0;

		enems_do ();
		player_move ();

#ifdef ENABLE_COCOS
		simplecoco_do ();
#endif		
		
#ifndef DISABLE_HOTSPOTS	
		hotspots_do ();
#endif

#ifdef BREAKABLE_WALLS
		breakable_do ();
#endif

#ifdef FLOATY_PUSH_BOXES
		fpb_do ();
#endif		

#ifdef ENABLE_HITTER
		hitter_do ();
#endif

		hud_update ();
		
#ifdef ENABLE_TIMED_MESSAGE
		timed_message_do ();
#endif		

		// Update screen
#ifdef SPECCY		
		if (isrc < 2) {
			#asm
				halt
			#endasm
		}
		isrc = 0;
#endif		
		
#ifdef CPC		
		while (isrc [0] < 12) {
			#asm 
				halt
			#endasm
		}
		isrc [0] = 0;
#endif
		
		// Update sprites
#if defined (CPC) && defined (TALL_PLAYER)
		gpit = SW_SPRITES_ALL; while (gpit --) if (spr_on [gpit]) {
			rdx = spr_x [gpit]; rdsint = spr_y [gpit] - 16;
			if (gpit == 0) rdsint -= 8;
			SPRITE_UPDATE_ABS (gpit, rdx, rdsint);
			SPRITE_CELL_PTR_UPDATE (gpit);
		} else SPRITE_OUT (gpit);
#else		
		gpit = SW_SPRITES_ALL; while (gpit --) if (spr_on [gpit]) {
			rdx = spr_x [gpit]; rdsint = spr_y [gpit] - 16;
			SPRITE_UPDATE_ABS (gpit, rdx, rdsint);
			SPRITE_CELL_PTR_UPDATE (gpit);
		} else SPRITE_OUT (gpit);
#endif

		SCREEN_UPDATE;

#ifdef SCRIPTING_ON
		if (f_zone_ac) {
			if (pry >= fzy1 && pry <= fzy2)
				if (prx >= fzx1 && prx <= fzx2)
					game_run_fire_script ();
		}
#endif
		
		// Moar
		if (pwashit) player_hit ();

		// Customize the ending condition
		if (pkilled 
			|| pobjs == c_level [MAX_HOTSPOTS_TYPE_1]
#ifdef SCRIPTING_ON			
			|| (script_result)
#endif			
#ifdef CHEAT_ON
			|| (CONTROLLER_LEFT(pad) && CONTROLLER_RIGHT(pad))
#endif			
		) do_game = 0;
	}

	MUSIC_STOP;
}

void game_title (void) {
#ifdef SPECCY	
	unpack_scr (TITLE_C);
	rdc = 71;
	rdx = 8; rdy = 8; p_s ("THE LOST LEVELS");
	rdx = 8; rdy = 13; p_s ("1.KEYS WASD N M/2.KEYS OPQA SP/3.KEMPSTON/4.SINCLAIR");
	rdx = 3; rdy = 22; p_s ("@ 2017 BY THE MOJON TWINS/@ 2017 MONUMENT MICROGAMES");

	SCREEN_UPDATE_NO_SPRITES;

#ifdef SE_BEEPER
	#asm
		call play_music
	#endasm
#endif	

	while (1) {
		gpit = KEY_ASCII - '0';
		if (gpit >= 1 && gpit <= 4) break;
	}

	controls_setup ();		// Setup controls.
#endif	

#ifdef CPC
	unpack_scr (TITLE_C);
	cpc_ShowTileMap (1);
	cpc_ResetTouchedTiles ();

	rdx = 3; rdy = 23; p_s_upd ("@ 2018 BY THE MOJON TWINS");
															   
	rdf = 1;
	while (rdf) {
		rdx = 6; rdy = 15; p_s_upd ("PRESS ESC TO REDEFINE/PRESS ENTER TO START");
		cpc_show_updated ();

		MUSIC_PLAY (M0_C);

		while (cpc_AnyKeyPressed());
		while (1) {
			if (cpc_TestKey (KEY_ESC)) {
				controls_setup (); break;
			} 
			if (cpc_TestKey (KEY_ENTER)) {
				rdf = 0; break;
			}
		}

		MUSIC_STOP;
	}
#endif
}

void game_over (void) {
	CLEAR_RECT (RECT_FULL_SCREEN);
	rdc = 71; rdx = 11; rdy = 12; p_s ("GAME UNDER!");
	SCREEN_UPDATE_NO_SPRITES;
	MUSIC_PLAY (M2_C);
#ifdef SPECCY
	SFX_PLAY (SFX_ITEM);
#endif
	wait_button ();
	MUSIC_STOP;
}

void game_ending (void) {
	MUSIC_PLAY (M0_C);
#ifdef SPECCY
	
#endif	
#ifdef CPC
	unpack_scr (ENDING_C); 
	cpc_ShowTileMap (1);
	cpc_ResetTouchedTiles ();
	rdc = 71; rdx = 2; rdy = 15; p_s_upd ("      CONGRATULATIONS!!// YOU GOT THE SWORD. SEE YOU//      IN THE ICE PALACE.");
	cpc_show_updated ();
	wait_button ();		
#endif	

	MUSIC_STOP;
	CLEAR_RECT (RECT_FULL_SCREEN);
	SCREEN_UPDATE_NO_SPRITES;
}

