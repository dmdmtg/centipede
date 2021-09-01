/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
#include "playdefs.h"
#define	CORMUSH (mushspace[mushx(worm[i].rect.corner.x-1)][mushy(worm[i].rect.corner.y-1)])
init_round ()
{
	int	i;
	
	for (i = 0; i < WORMMAX; i++) {
		SET_ATT (worm[i], EXISTS);
		CLEAR_ATT (worm[i], CLIMBMODE);
		CLEAR_ATT (worm[i], HIT_BOTTOM);
		
		/* place segment also */
		worm[i].looks = &wormlooks; /* Needed to find
						corner of worm seg. */
		worm[i].rect = raddp (worm[i].looks->rect,
					mushorigin ((i + 1), 1));
		/* The segment is never actually even with a mushroom. */
		worm[i].rect = raddp (worm[i].rect, Pt (8, 0));

		worm[i].dxdt = WORMXSPEED;
		worm[i].dydt = 0;
		CLEAR_ATT (worm[i], PLUMMETING);
		
		if ((i == WORMMAX-1) || CORMUSH) {
			SET_ATT (worm[i], IS_HEAD);
			worm[i].looks = &headlooks;
		}
		else {
			CLEAR_ATT (worm[i], IS_HEAD);
			worm[i].looks = &wormlooks;
		}
		put_object (worm[i]);
	}

	if (IS_SET(shot, EXISTS)) {
		CLEAR_ATT (shot, EXISTS);
		put_object (shot);
	}
	
	if (mush_cnt != 0) { /* Remove silliness	*/
		if (IS_SET (spider, EXISTS)) {
			put_object (spider);
			spider.looks = &spiderlooks;
			put_object (spider);
		}
		else
			spider.looks = &spiderlooks;
	}
	
	if (spidbuf[0] != '\0') { /* clear old score display */
		string (&defont, spidbuf, &display, spider.rect.origin, F_XOR);
		spidbuf[0] = '\0';
	}
	

	put_object (me);
}
