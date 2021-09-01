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

/* 'slugchoose' decides how the mushroom dropper should move next.
 */
slugchoose(objp)
struct	object	*objp;
{
	slug.next = raddp (slug.rect, Pt(slug.dxdt, slug.dydt));
	if (!(ptinrect(slug.next.corner, Drect))) {
		CLEAR_ATT (slug, EXISTS);
		put_object (slug);
		return (FALSE);
	}
	return (TRUE);
}
