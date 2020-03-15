// MT MK3 OM v0.3 [Sir Ababol NES_OM]
// Copyleft 2017, 2018 by The Mojon Twins

// Hud - customize here your hud routines.

void hud_update (void) {
	rdc = 71;
/*
	if (ptile_get_ctr != optile_get_ctr) {
		p_t2 (29, 0, ptile_get_ctr);
		optile_get_ctr = ptile_get_ctr;
	}
*/ 
	if (plife != oplife) {
		p_t2 (7, 1, plife);
		oplife = plife;
	}

	if (pobjs != opobjs) {
		p_t2 (18, 1, c_level [MAX_HOTSPOTS_TYPE_1] - pobjs);
		opobjs = pobjs;
	}

	if (pkeys != opkeys) {
		p_t2 (28, 1, pkeys);
		opkeys = pkeys;
	}
		
/*
	rdc = 15;

	if (pstars != opstars) {
		p_t2 (18, 23, pstars);
		opstars = pstars;
	}
*/
}
