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

/* 'disp_score' displays the value of 'score'.				*/


disp_score ()
{
	register	int	i;
	int	x;
	long	tempscr, prevtemp;
	
	if (score < 0)
		score = 0;
	tempscr = score;
	prevtemp = prevscore;

	x = div2 (Drect.origin.x + Drect.corner.x) - 96;

	/* show score */
	if (prevtemp == -1) {
		for (i = 5; i >= 0; i--) {
			bitblt (&N[tempscr%10], Rect (0, 0, 32, 30),
			&display, Pt(x + i * 32, Drect.origin.y), F_XOR);
			tempscr /= 10;
		}
	}
	else {
		for (i = 5; i >= 0; i--) {
			if ((tempscr % 10) != (prevtemp % 10)) {
			    bitblt (&N[prevtemp % 10], Rect(0, 0, 32, 30),
				&display, Pt(x + i * 32, Drect.origin.y), F_XOR);
			    bitblt (&N[tempscr % 10], Rect(0, 0, 32, 30),
				&display, Pt(x + i * 32, Drect.origin.y), F_XOR);
			}
			prevtemp /= 10;
			tempscr /= 10;
		}
	}
	if (score >= newmanat) {
		newmanat += NEWMANSTEP;
		me_cnt++;
		show_extra (me_cnt-1);
		/* make sounds */
		beep;
		nap(10);
		beep;
		nap(10);
		beep;
		nap(10);
	}
	prevscore = score;
}
