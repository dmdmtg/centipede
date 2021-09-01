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

/* 'init_scr' checks to make sure there's enugh room to display the game
 *	and then initializes that display.
 */
init_scr ()
{
	int	i, j, c,
		loop,
		putrow,
		putcol;

TOP:	request (KBD|MOUSE);
			
# ifdef MPX
	while (TRUE) {
		P->state &= ~RESHAPED;

		texture16 (&display, Drect, (own()&MOUSE? &plain : &fancy),
			 F_STORE);

		mushcols = (Drect.corner.x - Drect.origin.x)/MUSHWIDTH;
		mushrows = (Drect.corner.y - Drect.origin.y)/MUSHHEIGHT;
		if (mushrows <= 5 || mushcols <= 16) {
			beep;
			string (&defont, "Too small,",
				&display, Drect.origin, F_XOR);
			string (&defont, "reshape.",
				&display, add (Drect.origin, Pt(0, 12)),
				F_XOR);
			cursswitch ((Texture16*)0);
		}
		else
			break;
		while (!(P->state & RESHAPED)) {
			if (((c = kbdchar()) == 'q') || (c == 'Q')) {
				exit (0);
			}
			if ((bttn1() && (!ptinrect (mouse.xy, Drect))) ||
			    bttn3()) {
				serve_mouse ();
				cursswitch ((Texture16*) 0);
			}
			wait (CPU);
		}
	}
# else
	texture16 (&display, Drect, (own()&MOUSE? &plain : &fancy),
		   F_STORE);
	mushcols = (Drect.corner.x - Drect.origin.x)/MUSHWIDTH;
	mushrows = (Drect.corner.y - Drect.origin.y)/MUSHHEIGHT;
# endif
	string (&defont, "C E N T I P E D E",
		&display, sub(div(add(Drect.origin, Drect.corner), 2),
			      Pt(0, 30)), F_XOR);

	string (&defont, "Hit any key to start",
		&display, div(add(Drect.origin, Drect.corner), 2), F_XOR);

	while (kbdchar() == -1) {
		if ((bttn1() && (!ptinrect (mouse.xy, Drect))) ||
		    bttn3()) {
			serve_mouse ();
			cursswitch ((Texture16*) 0);
		}
		wait (CPU);
# ifdef MPX
		if (P->state & RESHAPED) {
			goto TOP;
		}
# endif MPX
	}

	cursswitch (&plain);
	texture16 (&display, Drect, (own()&MOUSE? &plain : &fancy), F_STORE);

	botrect.corner = mushorigin (mushcols, mushrows);

	playerrect.origin = mushorigin (0, (int) mushrows*3/4);
	playerrect.corner = botrect.corner;

	rectf (&display, Rect (playerrect.corner.x, Drect.origin.y,
				Drect.corner.x, Drect.corner.y),
	       F_XOR);
	rectf (&display, Rect (playerrect.origin.x, playerrect.corner.y,
				playerrect.corner.x, Drect.corner.y),
	       F_XOR);

	topofbottom = mushrows * 2 / 3;
	botrect.origin = mushorigin (0, topofbottom);

	for (i = 0; i < MUSHCOLS; i++)
		for (j = 0; j < MUSHROWS; j++) {
			mushspace[i][j] = 0;
			glowmush[i][j] = 0;
		}
	/* Place some initial Mushrooms */
	loop = (int) urnd (25, 40);
	mush_cnt = 0;
	botmush_cnt = 0;
	for (i = 0; i < loop; i++) {
		putcol = (int) urnd (0, mushcols);
		putrow = (int) urnd (2, mushrows-1);
		if (mushspace[putcol][putrow] == 0) {
			mush_cnt++;
			mushspace[putcol][putrow] = CHUNKMAX;
			bitblt (&mushlooks, mushlooks.rect, &display,
				mushorigin (putcol,putrow), F_XOR);
			if (putrow >= topofbottom)
				botmush_cnt++;
		}
	}
/*	rectf (&display, Rect(merect.origin.x, merect.origin.y,
			      merect.corner.x, merect.origin.y+1), F_XOR);
*/
	for (i = 1; i < ME_MAX; i++)
		show_extra (i);
	return (TRUE);
}
