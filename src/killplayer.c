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

/* 'killplayer' is called when the player has collided with an object.
 * 	Things are reset and the game may be exited as a result.
 */
killplayer (objp)
struct	object	*objp;
{
	int	i, j, k;
	
	for (i = 1; i <= 10; i++) {
		nap (25);
		if ((bttn1() && (!ptinrect (mouse.xy, Drect))) || bttn3())
			serve_mouse ();
		rectf (&display, me.rect, F_XOR);
	}
	put_object (me);

	if (IS_SET(slug, EXISTS)) {
		CLEAR_ATT(slug, EXISTS);
		put_object (slug);
	}
	if (IS_SET(spider, EXISTS)) {
		CLEAR_ATT (spider, EXISTS);
		put_object (spider);
		spider_fuse = SPIDERGONE;
	}
	if (spidbuf[0] != '\0') { /* clear old score display */
		string (&defont, spidbuf, &display, spider.rect.origin, F_XOR);
		spidbuf[0] = '\0';
	}
	
	if (IS_SET(scorpion, EXISTS)) {
		scorp_fuse = scorpgone ();
		CLEAR_ATT (scorpion, EXISTS);
		put_object (scorpion);
	}
	for (i = 0; i < WORMMAX; i++)
		if (IS_SET(worm[i], EXISTS)) {
			CLEAR_ATT(worm[i], EXISTS);
			put_object(worm[i]);
		}
	for (i = 0; i < mushcols; i++)
		for (j = 1; j < mushrows; j++) {
			if ((mushspace[i][j] != 0) &&
			    (mushspace[i][j] != CHUNKMAX)) {
				score += 5;
				disp_score ();
				for (k = mushspace[i][j]+1; k <= CHUNKMAX; k++)
					put_chunk (k, i, j);
				mushspace[i][j] = CHUNKMAX;
				nap (5);
			}
			if ((mushspace[i][j] != 0) &&
			    glowmush[i][j]) {
				bitblt(&glowlooks,glowlooks.rect, &display,
					mushorigin (i, j), F_XOR);
				glowmush[i][j] = FALSE;
				bitblt(&mushlooks,mushlooks.rect, &display,
					mushorigin (i, j), F_XOR);
			}
		}
	me_cnt--;

	if (me_cnt <= 0) {
		exit_game ();
		start_over = TRUE;
		return;
	}
	show_extra(me_cnt);
	init_round ();
}
