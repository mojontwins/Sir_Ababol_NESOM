// MT MK3 OM v0.3 [Sir Ababol NES_OM]
// Copyleft 2017, 2018 by The Mojon Twins

// Spaghetti

#ifdef SE_BEEPER
void beep_fx (unsigned char n);
#endif

void hotspots_load (void);

#ifdef SCRIPTING_ON
void game_run_fire_script (void);
#endif

#ifdef CPC
void cpc_show_updated (void);
void p_s_upd (unsigned char *s);
#endif
