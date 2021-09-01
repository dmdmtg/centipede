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

/* 'shotchoose' determines how the player's missile should move
 * next.
 */
shotchoose (objp)
struct	object	*objp;
{
	shot.next = raddp (shot.rect, Pt(shot.dxdt, shot.dydt));
	/* Check for going off the screen in shot_collision	*/
	return (TRUE);
}
