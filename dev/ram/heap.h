// MT MK3 OM v0.3 [Sir Ababol NES_OM]
// Copyleft 2017, 2018 by The Mojon Twins

// Reserves static space for everything.

// Look at the size of each kind of your *un*compressed files
// And give proper values to:
#define MAX_MAP_SIZE            2048
#define MAX_DECOS_SIZE          256
#define MAX_LOCKS_SIZE          16
#define MAX_ENEMS_SIZE          184 //256

// Tileset
extern const unsigned char ts [0];
extern const unsigned char tsmaps [0];
extern const unsigned char behs [0];

// Spriteset
extern const unsigned char ss [0];
extern const unsigned char ss_main [0];
extern const unsigned char ss_enems [0];
extern const unsigned char ss_extra [0];
extern const unsigned char ss_small [0];
#ifdef CPC
	extern const unsigned char ss_empty [0];
#endif	

// Map data
extern const unsigned char map [0];
#ifdef ENABLE_DECOS	
extern const unsigned char decos [0];
#endif
#ifdef HOTSPOT_TYPE_KEY
extern const unsigned char locks [0];
#endif

// Enems data
extern const unsigned char enems [0];

// Hotspots
extern const unsigned char hotspots [0];

#asm
	;; Patterns and tilemaps for the metatileset
#ifdef SPECCY
	._ts
		; First, the main font. Must be 64 chars (512 bytes) long.
		; BINARY "../bin/font.bin"
		; Then, space for the remaining 192 characters (1536 bytes).
		; defs 1536
		; In this game, the whole block is fixed, and tilemaps are 
		; created as per-level basis which use this pattern set:
		BINARY "../ports/zx/bin/ts.bin" ; 2048 bytes
#endif
#ifdef CPC 
		; _ts and tiles are defined and XREFd in tilemap_conf.asm	
#endif		
	._tsmaps
		; Space to define up to 48 metatiles (384 bytes).
		; defs 384
		; In this game, there is only one level.
#ifdef SPECCY
		BINARY "../ports/zx/bin/level0/ts.tilemaps.bin"
#endif
#ifdef CPC
		BINARY "../ports/cpc/bin/level0/ts.tilemaps.bin"
#endif		
	._behs
		; Space to describe up to 48 metatiles (48 bytes).
		; defs 48
		; In this game, there is only one level.
#ifdef SPECCY
		BINARY "../ports/zx/bin/level0/behs.bin"
#endif
#ifdef CPC
		BINARY "../ports/cpc/bin/level0/behs.bin"
#endif
	;; Sprite cells

#ifdef SPECCY
	._ss
		; Dummy 8 empty (masked) spaces for vertical rotation
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
#endif		
	._ss_main
		; First, space for / include the main characters
#ifdef SPECCY		
		BINARY "../ports/zx/bin/ssmain.bin"
#endif		
#ifdef CPC
		BINARY "../ports/cpc/bin/ssmain.bin"
#endif		
	._ss_enems
		; Second, space for the enemies / etc.
		; SPRITES_EXTRA_CELLS masked cells (144 * EXTRA_SPRITES)
#ifdef SPECCY		
		; defs SPRITES_EXTRA_CELLS * 144
		BINARY "../ports/zx/bin/level0/ss.bin"
#endif
#ifdef CPC
		; defs SPRITES_EXTRA_CELLS * 64
		BINARY "../ports/cpc/bin/level0/ss.bin"
#endif		
	._ss_extra
		; Third, assorted extra stuff
		; Explosion
		; cell 16
#ifdef SPECCY		
		BINARY "../ports/zx/bin/ssextra.bin"
#endif	
#ifdef CPC
		BINARY "../ports/cpc/bin/ssextra.bin"
#endif		
	._ss_small
		; Extra space for projectiles, etc.
#ifdef SPECCY
		; defs SPRITES_SMALL_CELLS * 64
		BINARY "../ports/zx/bin/sssmall.bin"
#endif
#ifdef CPC
		; defs SPRITES_SMALL_CELLS * 64
		BINARY "../ports/cpc/bin/sssmall.bin"
#endif
#ifdef CPC
	._ss_empty
		; a 100% transparent sprite
		BINARY "../ports/cpc/bin/ssempty.bin"
#endif		

	;; Map data + index
	._map
/*
#if defined(MAP_FORMAT_RLE53) || defined (MAP_FORMAT_RLE44) || defined (MAP_FORMAT_BYTE_RLE)
		; You can adjust the amount of reserved bytes to the size of your
		; biggest map when it is in its original RLE format.
		defs MAX_MAP_SIZE
#elif defined (MAP_FORMAT_PACKED)
		defs MAX_PANTS*75
#elif defined (MAP_FORMAT_UNPACKED)
		defs MAX_PANTS*150
#endif
*/
		; there is only one non-destructible level in this game
#ifdef SPECCY
		BINARY "../ports/zx/bin/level0/map.bin"
#endif
#ifdef CPC
		BINARY "../ports/cpc/bin/level0/map.bin"
#endif

#ifdef ENABLE_DECOS		
	._decos
		; You can adjust the amount of reserved bytes to the size of your
		; biggest set of map decorations.
		defs MAX_DECOS_SIZE
#endif

#ifdef HOTSPOT_TYPE_KEY
	._locks
		; You can adjust the amount of reserved bytes to the size of your
		; biggest set of locks.
		; defs MAX_LOCKS_SIZE
		; In this game, there is just one set of locks.
#ifdef SPECCY		
		BINARY "../ports/zx/bin/level0/locks.bin"
#endif
#ifdef CPC
		BINARY "../ports/cpc/bin/level0/locks.bin"
#endif
#endif

	;; Enems data + index
	._enems
		; You can adjust the amount of reserved bytes to the size of you.
		; biggest set of enemies.
		; defs MAX_ENEMS_SIZE
		; there is only one level in this game
#ifdef SPECCY
		BINARY "../ports/zx/bin/level0/enems.bin"
#endif
#ifdef CPC
		BINARY "../ports/cpc/bin/level0/enems.bin"
#endif		

	;; Hotspots

	._hotspots
		; reserve two bytes per screen
		;defs 2*MAX_PANTS
		; there is only one level in this game
#ifdef SPECCY
		BINARY "../ports/zx/bin/level0/hotspots.bin"
#endif
#ifdef CPC
		BINARY "../ports/cpc/bin/level0/hotspots.bin"
#endif		
#endasm
