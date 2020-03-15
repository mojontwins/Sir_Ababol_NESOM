// MT MK3 OM v0.3 [Sir Ababol NES_OM]
// Copyleft 2017, 2018 by The Mojon Twins

// Hotspots

void hotspots_ini (void) {
	#ifdef HOTSPOTS_MAY_CHANGE
		gp_gen = (unsigned char *) (hotspots);
		for (gpit = 0; gpit < MAX_PANTS; ++gpit) {
			ht [gpit] = *gp_gen ++; gp_gen ++;
			hact [gpit] = 1;
		}
	#else
		gpit = MAX_PANTS; while (gpit --) hact [gpit] = 1;
	#endif
}

void hotspots_load (void) {
	if (hact [n_pant]) {
		#ifdef HOTSPOTS_MAY_CHANGE
			rda = hotspots [1 + (n_pant << 1)];
			hrt = ht [n_pant];
		#else
			gp_gen = (unsigned char *) (hotspots + (n_pant << 1));
			hrt = *gp_gen ++; rda = *gp_gen;
		#endif
		hry = rda & 0xf0; hrx = rda << 4;

		if (hrt) {
			rdy = SCR_Y + (((rda >> 4) - 1) << 1); 
			rdx = SCR_X + ((rda & 0x0f) << 1);
			#ifdef HOTSPOT_SIMPLE_SIGNS
				rdt = HOTSPOTS_BASE_TILE + (hrt & 0xf);
			#else			
				rdt = HOTSPOTS_BASE_TILE + hrt;
			#endif			
			DRAW_TILE_UPD ();
		}
	} else hrt = 0;
}

void hotspots_do (void) {

	if (hrt) {
		if (collide (prx, pry, hrx, hry)) {
			#ifdef HOTSPOTS_LOGIC_MORE_COMPLEX
				rda = 1;
			#endif

			#ifdef HOTSPOT_SIMPLE_SIGNS
				switch (hrt & 0xf)
					case HOTSPOT_SIMPLE_SIGNS:
						if (CONTROLLER_DOWN (pad)) {
							rdt = hrt >> 4;
							text_window ();
						}
						rda = 0;
						break;
			#else			
				switch (hrt)
			#endif
			{

			#ifdef HOTSPOT_TYPE_REFILL
				case HOTSPOT_TYPE_REFILL:
					plife += LIFE_REFILL; if (plife > 99) plife = 99;
					break;
			#endif

			#ifdef HOTSPOT_TYPE_OBJECT
				case HOTSPOT_TYPE_OBJECT:
					#ifdef ONLY_ONE_OBJECT_FLAG
						if (flags [ONLY_ONE_OBJECT_FLAG]) {
							rda = 0;
						} else {
							flags [ONLY_ONE_OBJECT_FLAG] = 1;
						}
					#else				
						pobjs ++;
					#endif
					break;
			#endif

			#ifdef HOTSPOT_TYPE_KEY
				case HOTSPOT_TYPE_KEY:
					pkeys ++;
					break;
			#endif

			#ifdef HOTSPOT_TYPE_AMMO
				case HOTSPOT_TYPE_AMMO:
					if (AMMO_MAX - pammo < AMMO_REFILL) pammo = AMMO_MAX; else pammo += AMMO_REFILL;
					break;
			#endif

			#ifdef HOTSPOT_TYPE_STAR
				case HOTSPOT_TYPE_STAR:
					pstars ++;
					break;
			#endif
			}
			
			#ifdef HOTSPOTS_LOGIC_MORE_COMPLEX
				if (rda)
			#endif
			{
				SFX_PLAY (SFX_ITEM);
				
				// Delete hotspot
				rdy = (hry >> 4) - 1; rdx = hrx >> 4; 
				#ifdef HOTSPOTS_RESTORE_WITH_MAP_DATA				
					rdt = scr_buff [(rdy << 4) | rdx];
				#else
					rdt = 0;
				#endif
				set_map_tile ();

				hact [n_pant] = hrt = 0;
			}
		}
	}
}
