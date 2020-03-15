// MT MK3 OM v0.3 [Sir Ababol NES_OM]
// Copyleft 2017, 2018 by The Mojon Twins

// Organize stuff to make it useable to the engine.

// Pointers to sprite cells in the heap:

// Add more if you need them, and customize the init function

#ifdef SPECCY
#define MAX_CELLS_16x16 	17
#define MAX_CELLS_16x8		0
#define MAX_CELLS_8x16		0
#define MAX_CELLS_8x8		0
#define MAX_CELLS 			(MAX_CELLS_8x8+MAX_CELLS_16x8+MAX_CELLS_8x16+MAX_CELLS_16x16)

unsigned char *sprite_cells [MAX_CELLS];

	void sprite_cells_init (void) {
		rda = 0; 

		// 16x16 cells
		gp_gen = ss_main; gpit = MAX_CELLS_16x16; while (gpit --) {
			sprite_cells [rda ++] = gp_gen;
			gp_gen += 144;
		}

		// 8x8 cells
		gp_gen = ss_small; gpit = MAX_CELLS_8x8; while (gpit --) {
			sprite_cells [rda ++] = gp_gen;
			gp_gen += 64;
		}
	}
#endif

#ifdef CPC

#ifdef TALL_PLAYER
	#define MAX_CELLS_8x24		8			// Main player
	#define MAX_CELLS_8x16 		8+1+1+1		// 8 frames enems + extra + small + empty
	#define MAX_CELLS 			(MAX_CELLS_8x24+MAX_CELLS_8x16)

	unsigned char *sprite_cells [MAX_CELLS];
	void sprite_cells_init (void) {
		rda = 0; 

		gp_gen = ss_main; gpit = MAX_CELLS_8x24; while (gpit --) {
			sprite_cells [rda ++] = gp_gen;
			gp_gen += 96;
		}

		gp_gen = ss_enems; gpit = MAX_CELLS_8x16; while (gpit --) {
			sprite_cells [rda ++] = gp_gen;
			gp_gen += 64;
		}
	}
#else
	// All sprites are the same size (8x16)
	#define MAX_CELLS 			21
	unsigned char *sprite_cells [MAX_CELLS];
	void sprite_cells_init (void) {
		rda = 0; 
		
		gp_gen = ss_main; gpit = MAX_CELLS; while (gpit --) {
			sprite_cells [rda ++] = gp_gen;
			gp_gen += 64;
		}
	}
#endif
#endif
