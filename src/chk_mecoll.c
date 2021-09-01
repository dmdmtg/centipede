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

/* 'chk_mecollision' sees if the player bumped into anything. */
chk_mecollision()
{
	int	i;
	
	if (rectXrect (me.rect, spider.rect) &&
	    IS_SET(spider, EXISTS) && objXobj (&me, &spider)) {
		killplayer (&spider);
		return;
	}
	if (rectXrect (me.rect, slug.rect) &&
	    IS_SET (slug, EXISTS) && objXobj (&me, &slug)) {
		killplayer (&slug);
		return;
	}
	for (i = 0; i < WORMMAX; i++) {
		if (rectXrect(me.rect, worm[i].rect) &&
		    IS_SET(worm[i], EXISTS) && objXobj(&me, &worm[i])) {
			killplayer (&worm[i]);
			return;
		}
	}
}
