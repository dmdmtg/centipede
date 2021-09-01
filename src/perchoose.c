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

/* 'personchoose' ('*objp' == me for this one) */

personchoose (objp)
struct	object	*objp;
{
	int	i, c;
	Point	displace;
# ifdef BUMPMUSH
	unsigned char	top, right, left, bottom;
# endif

	if ((!IS_SET(shot, EXISTS))) {
		if (bttn2()) {
			SET_ATT(shot, EXISTS);
			shot.rect = raddp (shot.looks->rect,
					   Pt(div2(me.rect.corner.x +
						   me.rect.origin.x),
					      me.rect.origin.y));
			put_object (shot);
		}
# ifdef MPX
		else if ((bttn1() && (!ptinrect (mouse.xy, Drect))) ||
			   bttn3()) {
			serve_mouse ();
			if (P->state & RESHAPED) {
				start_over = TRUE;
				return (FALSE);
			}
		}
# endif
	}
	if (own() & KBD) {
		while ((c = kbdchar()) != -1) {
			switch (c) {
				case 'q':
				case 'Q':
					exit_game();
					start_over = TRUE;
					return (FALSE);
			}
		}
	}
	displace = sub (mouse.xy, oldmouse);
	if ((displace.x == 0) && (displace.y == 0))
		return (FALSE);
	me.next = raddp (me.rect, displace);

	if (me.next.origin.x < playerrect.origin.x)
		me.next = raddp (me.looks->rect, Pt (playerrect.origin.x,
						  me.next.origin.y));
	else if (me.next.corner.x > playerrect.corner.x) {
		me.next.corner.x = playerrect.corner.x;
		me.next.origin.x = playerrect.corner.x - MEWIDTH;
	}

	if (me.next.origin.y < playerrect.origin.y)
		me.next = raddp (me.looks->rect, Pt (me.next.origin.x,
						  playerrect.origin.y));
	else if (me.next.corner.y > playerrect.corner.y) {
		me.next.origin.y = playerrect.corner.y - MEHEIGHT;
		me.next.corner.y = playerrect.corner.y;
	}
# ifdef BUMPMUSH
	top = mushy(me.next.origin.y);
	bottom = mushy(me.next.corner.y-1);
	left = mushx(me.next.origin.x);
	right = mushx(me.next.corner.x-1);
	if (mushspace[left][top] || mushspace[left][bottom]) {
		if (me.next.origin.x < me.rect.origin.x)
			me.next.origin.x = Drect.origin.x + (right)<<5;
	}
	if (mushspace[right][top] || mushspace[right][bottom]) {
		if (me.next.origin.x > me.rect.origin.x)
			me.next.origin.x = Drect.origin.x + (left)<<5;
	}
	if (mushspace[right][top] || mushspace[left][top]) {
		if (me.next.origin.y < me.rect.origin.y)
			me.next.origin.y = Drect.origin.y + (bottom)<<5;
	}
	if (mushspace[right][bottom] || mushspace[left][bottom]) {
		if (me.next.origin.y > me.rect.origin.y)
			me.next.origin.y = Drect.origin.y + (top)<<5;
	}
	me.next.corner = add (me.next.origin, me.looks->rect.corner);
# endif
	oldmouse = me.next.origin;
	cursset (me.next.origin);
	return (TRUE);
}
