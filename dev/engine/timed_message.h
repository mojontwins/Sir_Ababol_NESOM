// MT MK3 OM v0.3 [Sir Ababol NES_OM]
// Copyleft 2017, 2018 by The Mojon Twins

// A simple timed message.

void timed_message_vars (void) {
	rdx = TM_X; rdy = TM_Y; rdc = TM_ATTR;
}

void timed_message_do (void) {
	if (tm_ctr) {
		tm_ctr --;
		if (0 == tm_ctr) {
			timed_message_vars ();
#ifdef SPECCY
			p_s (TM_ERASE);
#endif
#ifdef CPC
			p_s_upd (TM_ERASE);
#endif
		}
	}
}

void timed_message_print (unsigned char *m) {
	timed_message_vars ();
#ifdef SPECCY
	p_s (m);
#endif
#ifdef CPC
	p_s_upd (m);
#endif
	tm_ctr = TM_FRAMES;
}
