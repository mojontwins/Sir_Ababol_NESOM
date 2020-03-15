// MT MK3 OM v0.3 [Sir Ababol NES_OM]
// Copyleft 2017, 2018 by The Mojon Twins

// levelset.h
// Manually compiled assets lists for levels

// Costomize as needed

// If you need constants as declared by the converters,
// Add / include them here

#ifdef SPECCY
	#include "..\ports\speccy\bin\level0\enems.h"
	#include "..\ports\speccy\bin\level0\hotspots.h"
#endif
#ifdef CPC
	#include "..\ports\cpc\bin\level0\enems.h"
	#include "..\ports\cpc\bin\level0\hotspots.h"
#endif

// For me each level is:

// ts_tilemaps
// behs
// map
// enems
// hotspots
// script index in script pool
// ini_x (tiles)
// ini_y (tiles)
// scr_ini
// map_width

#define SCRIPT_INDEX		0
#define PLAYER_INI_X		1
#define PLAYER_INI_Y		2
#define PLAYER_SCR_INI		3
#define LEVEL_MAP_W			4
#define MAX_HOTSPOTS_TYPE_1	5

const unsigned char level0[] = {
	0,
	3, 3, 
	0,
	16,
	MAX_HOTSPOTS_0_TYPE_1
};

const unsigned char * levels [] = {
	level0
};
