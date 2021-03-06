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

/* 'spidstart' initializes spider related varibles.
 */
spidstart()
{
	int	spiderrow,
		sxspeed;
	
	/* We don't want the spider to be able to jump over the player	*/
	sxspeed = min (SPIDERSPEED + round_cnt, SPIDERWIDTH + MEWIDTH);
	spider.dydt = min (SPIDERSPEED + round_cnt, SPIDERHEIGHT + MEHEIGHT);
			
	if (spidbuf[0] != '\0') { /* clear old score display */
		string (&defont, spidbuf, &display, spider.rect.origin, F_XOR);
		spidbuf[0] = '\0';
	}
	SET_ATT (spider, EXISTS);
	spiderrow = urnd (0, (botrect.corner.y - SPIDERHEIGHT)
			      - botrect.origin.y);
	if (me.rect.origin.x < ((Drect.corner.x + Drect.origin.x)/2)) {
		spider.rect = raddp (spider.looks->rect, botrect.origin);
		spider.rect = raddp (spider.rect, Pt(0, spiderrow));
		spider.dxdt = sxspeed;
	}
	else {
		spider.rect = raddp (spider.looks->rect,
				     Pt (botrect.corner.x - SPIDERWIDTH,
					 botrect.origin.y));
		spider.rect = raddp (spider.rect, Pt(0, spiderrow));
		spider.dxdt = -sxspeed;
	}
	put_object(spider);
}

/* 'scorpstart' initializes scorpion related variables.
 */
scorpstart()
{
	int	scorprow,
		scorpcol;
		
	SET_ATT (scorpion, EXISTS);
	
	if (urnd (0, 20) < 1)
		scorprow = 1;
	else
		scorprow = urnd (1, topofbottom);

	if (urnd(0, 2) < 1) {
		scorpcol = 0;
		scorpion.dxdt = SCORPSPEED;
	}
	else {
		scorpcol = mushcols-1;
		scorpion.dxdt = -SCORPSPEED;
	}
	scorpion.rect = raddp (scorpion.looks->rect, mushorigin (scorpcol,
								scorprow));
	put_object (scorpion);
}

/* 'slugstart' initializes all mushroom dropper related varibles.
 */
slugstart()
{
	int	slugcol;
	
	SET_ATT (slug, EXISTS);
	slugcol = urnd (0, mushcols);
	slug.rect = raddp (slug.looks->rect, mushorigin (slugcol, 1));
	slug.dydt = SLOWSLUG;
	put_object(slug);
}
