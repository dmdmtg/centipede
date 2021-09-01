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

/* 'error' is used almost nowhere to show fatal error messages and
 *	exit.
 */
error (str)
char	*str;
{
	string(&defont, str, &display, Drect.origin, F_XOR);
	exit (1);
}
