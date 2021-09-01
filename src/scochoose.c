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

/* 'scorpchoose' helps a scorpion decide where it should move next.
 */
scorpchoose (objp)
struct	object	*objp;
{
	scorpion.next = raddp (scorpion.rect, Pt (scorpion.dxdt, 0));
	if (((scorpion.dxdt > 0) &&
	     (!(ptinrect(scorpion.next.corner, Drect)))) ||
	    ((scorpion.dxdt < 0) &&
	     (!(ptinrect(scorpion.next.origin, Drect))))) {
		CLEAR_ATT (scorpion, EXISTS);
		put_object (scorpion);
		scorp_fuse = scorpgone ();
		return (FALSE);
	}
	return (TRUE);
}
