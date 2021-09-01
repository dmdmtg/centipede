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

/* 'init_game' initializes everything for the beginning of a new
 * game.
 */
init_game ()
{
	int	i, c;
	
	score = 0;
	prevscore = -1; /* For updating the score display correctly	*/
	for (i = 0; i < WORMMAX; i++) {
		worm[i].dirchoose = wormchoose;
		worm[i].value = WORMVALUE;
	}
	/* Set spider, shot, scorpion, slug to "off" */
	CLEAR_ATT (shot, EXISTS);
	CLEAR_ATT (slug, EXISTS);
	CLEAR_ATT (spider, EXISTS);
	CLEAR_ATT (scorpion, EXISTS);
	scorp_fuse = scorpgone ();
	spider_fuse = SPIDERGONE;
	round_cnt = 0;
	me_cnt = ME_MAX;
	newmanat = NEWMANSTEP;
	
	spidbuf[0] = '\0';

	init_scr ();
	me.rect = raddp (me.looks->rect, mouse.xy);

	if (me.rect.origin.x < playerrect.origin.x)
		me.rect = raddp (me.looks->rect, Pt (playerrect.origin.x,
						  me.rect.origin.y));
	else if (me.rect.corner.x > playerrect.corner.x) {
		me.rect.corner.x = playerrect.corner.x;
		me.rect.origin.x = playerrect.corner.x - MEWIDTH;
	}

	if (me.rect.origin.y < playerrect.origin.y)
		me.rect = raddp (me.looks->rect, Pt (me.rect.origin.x,
						  playerrect.origin.y));
	else if (me.rect.corner.y > playerrect.corner.y) {
		me.rect.origin.y = playerrect.corner.y - MEHEIGHT;
		me.rect.corner.y = playerrect.corner.y;
	}
	cursset (me.rect.origin);
	oldmouse = me.rect.origin;
	return;
}
