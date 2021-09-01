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

Point	oldmouse;	/* Where the mouse was at last check	*/
Rectangle	botrect, /* Area of screen spider stays in. */
		playerrect; /* Area of screen player stays in.*/

#ifdef mc68000
Texture16	plain = {
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000
};

Texture16	fancy = {
	0x1000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000
};

#else
Texture plain = {
	0x00000000, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0x00000000, 0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

Texture fancy = {
	0x10001000, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0x10001000, 0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
#endif

i4	mush_bits[] = { /* What a mushroom looks like	*/
	0x001FF000,
	0x007FFE00,
	0x03FF1F80,
	0x0FC303C0,
	0x1F0600E0,
	0x1C060030,
	0x38060038,
	0x7805800C,
	0x6000800E,
	0xE0010006,
	0xE0020003,
	0xC0000003,
	0xC7F3FF43,
	0xC5DFDFBB,
	0xCF5DFCFA,
	0x7FFF3FFE,
	0x34FC2DEC,
	0x3FF67F5C,
	0x1EDE76F8,
	0x03FE3BE0,
	0x00FC3F80,
	0x001E3800,
	0x00341800,
	0x002C1800,
	0x006C4C00,
	0x00F8CC00,
	0x00F8C600,
	0x0171C700,
	0x01F9C300,
	0x03D7E180,
	0x02FFFFC0,
	0x07F87DC0
};

Bitmap	mushlooks = { /* For displaying mushrooms	*/
	(Word*) mush_bits,
	BLTWIDTH,
	{ { 0, 0 }, { 32, 32 } }
};

Bitmap	chunk1looks = { /* for displaying top mushroom chunk	*/
	(Word*) mush_bits,
	BLTWIDTH,
	{ { 0, 0 }, { 32, 8 } }
};

Bitmap	chunk2looks = { /* for displaying 2nd mushroom chunk	*/
	(Word*) &mush_bits[8],
	BLTWIDTH,
	{ { 0, 0 }, { 32, 8 } }
};

Bitmap	chunk3looks = { /* for displaying 3rd mushroom chunk	*/
	(Word*) &mush_bits[16],
	BLTWIDTH,
	{ { 0, 0 }, { 32, 8 } }
};

Bitmap	chunk4looks = { /* for displaying bottom mushroom chunk	*/
	(Word*) &mush_bits[24],
	BLTWIDTH,
	{ { 0, 0 }, { 32, 8 } }
};

i4	glow_bits[] = { /* What full glowing mushroom looks like	*/
	0x001FF000,
	0x007FFE00,
	0x03FFFF80,
	0x0FFFFFC0,
	0x1F8FE7E0,
	0x1F0FC3F0,
	0x3F0FC3F8,
	0x7FFFFFFC,
	0x7FFFFFFE,
	0xFFFFFFFE,
	0xF3FFFFEF,
	0xF8FFFF8F,
	0xF87FFF0F,
	0xFC0FF81F,
	0xFC00007E,
	0x7E00007E,
	0x3F8000FC,
	0x3FE007FC,
	0x1FFFFFF8,
	0x03FFFFE0,
	0x001FFF80,
	0x001FF000,
	0x003FF800,
	0x003FF800,
	0x007FFC00,
	0x00FFFC00,
	0x00FFFE00,
	0x01FFFF00,
	0x01FFFF00,
	0x03FFFF80,
	0x03FFFE00,
	0x03F87C00
};

Bitmap	glowlooks = { /* For displaying full glowing mushroom	*/
	(Word*) glow_bits,
	BLTWIDTH,
	{ { 0, 0 }, { 32, 32 } }
};

Bitmap	gl1looks = { /* For displaying top glowing mushroom chunk	*/
	(Word*) glow_bits,
	BLTWIDTH,
	{ { 0, 0 }, { 32, 8 } }
};

Bitmap	gl2looks = { /* For displaying 2nd glowing mushroom chunk	*/
	(Word*) &glow_bits[8],
	BLTWIDTH,
	{ { 0, 0 }, { 32, 8 } }
};

Bitmap	gl3looks = { /* For displaying 3rd glowing mushroom chunk	*/
	(Word*) &glow_bits[16],
	BLTWIDTH,
	{ { 0, 0 }, { 32, 8 } }
};

Bitmap	gl4looks = { /* For displaying bottom glowing mushroom chunk	*/
	(Word*) &glow_bits[24],
	BLTWIDTH,
	{ { 0, 0 }, { 32, 8 } }
};

i4	me_bits[] = { /* What the player looks like	*/
	0x00018000,
	0x00018000,
	0x0003C000,
	0x0007E000,
	0x000E7000,
	0x001E7800,
	0x00381C00,
	0x00700E00,
	0x00E00700,
	0x01C00380,
	0x038001C0,
	0x070000E0,
	0x0E000070,
	0x1C000038,
	0x3800001C,
	0x7000000E,
	0xE180018F,
	0xE3C003C7,
	0xE3C003C7,
	0xE1800187,
	0xE0000007,
	0xE0000007,
	0xFFC003FF,
	0x7FE007FE,
	0x00E00700,
# ifndef BUMPMUSH
	0x00600600,
	0x00600600,
	0x00600600,
	0x00600600,
# endif
	0x00600600,
	0x007FFE00,
	0x007FFE00
};

Bitmap	melooks = { /* For displaying player	*/
	(Word*) me_bits,
	BLTWIDTH,
# ifdef BUMPMUSH
	{ { 0, 0 }, { 32, 28 } }
# else
	{ { 0, 0 }, { 32, 32 } }
# endif
};


i4	scorp_bits[] = { /* What scorpion looks like	*/
	0x00E00000, 0x00100000,
	0x03FC0000, 0x00100000,
	0x07FE0000, 0x01500000,
	0x3FFE0000, 0x01500000,
	0x3FFF0000, 0x01B00000,
	0x3FC70000, 0x00A80000,
	0x7E070000, 0x00B80000,
	0x7C070000, 0x00980000,
	0x7C020000, 0x01F80000,
	0xF8060203, 0x01F80000,
	0xF80E0383, 0x81F80000,
	0xF8380286, 0x03F80000,
	0xF8000604, 0x07F80000,
	0xFC004484, 0x0FF80000,
	0xFE01E4C4, 0x1FF80000,
	0x7F0325E4, 0x3FF80000,
	0x7F801D34, 0x7FF00000,
	0x7FE00C0C, 0xFFE00000,
	0x3FFFFFFF, 0xFFC00000,
	0x1FFFFFFF, 0xFF800000,
	0x0FFFFFFF, 0xFF000000,
	0x07FFFFFF, 0xFE000000,
	0x03FFFFFF, 0xFC000000,
	0x007FFFFF, 0xF0000000
	};

Bitmap	scorplooks = { /* For displaying scorpion	*/
	(Word*) scorp_bits,
	BLTWIDTH * 2,
	{ { 0, 0 }, { 48, 24 } }
};

i4	shot_bits[] = { /* What player's missile looks like	*/
	0xE0000000,
	0xE0000000,
	0xE0000000,
	0xE0000000,
	0xE0000000,
	0xE0000000,
	0xE0000000,
	0xE0000000,
	0xE0000000,
	0xE0000000,
	0x00000000,
	0x00000000,
	0xE0000000,
	0xE0000000,
	0xE0000000,
	0xE0000000,
	0xE0000000,
	0xE0000000,
	0xE0000000,
	0xE0000000,
	0xE0000000,
	0xE0000000,
	0xE0000000,
	0xE0000000,
	0xE0000000,
	0xE0000000
};

Bitmap	shotlooks = { /* For displaying	player's missile	*/
	(Word*) shot_bits,
	BLTWIDTH,
	{ { 0, 0 }, { 3, 26 } }
};


i4	slug_bits[] = { /* What a slug (mushroom dropper) looks like	*/
	0x007FFE00,
	0x01FFFF80,
	0x7FFFFFFE,
	0xFFE1D3FF,
	0x0380C3C0,
	0x03781EF0,
	0x07FC3FFA,
	0x0FCC33FA,
	0x1FB42DFC,
	0x33B4ADDC,
	0x7385E1CE,
	0x63CDB3C7,
	0xC1FD9F83,
	0xC1FD9F83,
	0xC0FB0F13,
	0xD8030013,
	0xC2060003,
	0xC31E0303,
	0xC01C0003,
	0xCC3C7023,
	0xC03CDB11,
	0xE23FF807,
	0xE2003007,
	0x7000001F,
	0x3EADFFFE,
	0x1FFFFFFC,
	0x00E1C380,
	0x00F3E7C0,
	0x01FBE7E0,
	0x07BBEE70,
	0x0F0FFC38,
	0x0E07F83C
};

Bitmap	sluglooks = { /* For displaying slug (mushroom dropper) */
	(Word*) slug_bits,
	BLTWIDTH,
	{ { 0, 0 }, { 32, 32 } }
};


i4	spid_bits[] = { /* What spider looks like	*/
	0x00001FFF, 0x80000000,
	0x00003FFF, 0xE0000000,
	0x0000FFFF, 0xE0000000,
	0x0001FFFF, 0xFFE00000,
	0x0003FFFF, 0xFDF00000,
	0x0003FFFF, 0xF0380000,
	0x001FFFFF, 0xF0380000,
	0x007FFFFF, 0xFC1C0000,
	0x01C7FFFF, 0xFF0C0000,
	0x0307FFFF, 0xFF8E0000,
	0x0607FFFF, 0xF8C60000,
	0x040FFFFF, 0xF0670000,
	0x0C1BFFFF, 0xC0630000,
	0x0C3BFFFF, 0xE0630000,
	0x0873FFFC, 0x78310000,
	0x1863BFFF, 0x78310000,
	0x19C333FB, 0x3C300000,
	0x110633FB, 0xBC300000,
	0x330C73FB, 0x9C300000,
	0x37186369, 0x8C100000,
	0x261061F1, 0x8E180000,
	0x643060E1, 0x8E180000,
	0xCC20E001, 0x8E180000,
	0x4860E001, 0x0E180000,
	0x1860E001, 0x0E180000,
	0x1860C003, 0x06080000,
	0x18E0C003, 0x06000000,
	0x18C0C003, 0x06000000,
	0x11C0C003, 0x04000000,
	0x00808001, 0x00000000
};

Bitmap	spiderlooks = { /* For displaying spider	*/
	(Word*) spid_bits,
	BLTWIDTH * 2,
	{ { 0, 0 }, { 48, 30 } }
};

i4	face_bits[] = {
	0x00018000, 0x00000000,
	0x000FE000, 0x00000000,
	0x003BB800, 0x00000000,
	0x00EC8FF8, 0x00000000,
	0x03FFD7CC, 0x00000000,
	0x05F39990, 0x00000000,
	0x0DF73F9C, 0x00000000,
	0x1FFBFBF3, 0x00000000,
	0x1FEA7B7F, 0x00000000,
	0x1FE73F4F, 0x00000000,
	0x1FF12F3F, 0x80000000,
	0x3F59DE3F, 0xC0000000,
	0x3F3FFE3F, 0xC0000000,
	0x2DCFF0DB, 0xC0000000,
	0x2FFBC3ED, 0xC0000000,
	0x278E001E, 0xC0000000,
	0x7FF00007, 0xE0000000,
	0x6E000007, 0xF0000000,
	0x3CFF0FE3, 0xE0000000,
	0x39FF9FF1, 0xA0000000,
	0x3B01F818, 0xA0000000,
	0x3339FB98, 0xE0000000,
	0x7F399B9F, 0xC0000000,
	0x7F399B9F, 0xC0000000,
	0x2B076C19, 0x40000000,
	0x2BFE47F9, 0x40000000,
	0x29FC93F1, 0x40000000,
	0x28001001, 0x40000000,
	0x28001001, 0x40000000,
	0x18010801, 0x40000000,
	0x08010801, 0x82F80000,
	0x0800D803, 0x07BC0000,
	0x0C000002, 0x08860000,
	0x060DFE84, 0x0FFE0000,
	0x031B5FC4, 0x0FFE0000,
	0x011D018C, 0x0C060000,
	0x01880088, 0x7D560000,
	0x00C1FC18, 0xFD560000,
	0x00400031, 0xDD560000,
	0x00200061, 0x8D560000,
	0x003000C1, 0x8D560000,
	0xE0107081, 0x8D560000,
	0xA0180081, 0x8D560000,
	0xEEE40181, 0xDD560000,
	0x8AA77F00, 0xFD560000,
	0x8EE18000, 0x2D560000,
	0x8AA00000, 0x0C060000,
	0x00000000, 0x0FFE0000
};

Bitmap	facelooks = {
	(Word*) face_bits,
	BLTWIDTH * 2,
	{ { 0, 0 }, { 48, 48 } }
};


i4	worm_bits[] = { /* What a centipede non-head segment looks like	*/
	0x0007E000,
	0x003FF800,
	0x00FFEE00,
	0x03E03F80,
	0x07BFF7C0,
	0x076DC9F0,
	0x0F8F0878,
	0x1E173E38,
	0x3C750ABC,
	0x34E88B9C,
	0x77B00B0E,
	0x67F88E07,
	0xC41C9E3B,
	0xD827835B,
	0xDC46E4C3,
	0xF5C448E3,
	0xE6E41397,
	0xC29C3D93,
	0xFD9C6713,
	0xC7F8031F,
	0xC94080F9,
	0xF0C78337,
	0xE2833E37,
	0x73CF803F,
	0x3EFDFFFE,
	0x1FFFFFFC,
	0x00E00380,
	0x00F007C0,
	0x01FC07E0,
	0x07BE0E70,
	0x0F0E1C38,
	0x0E06383C
};

Bitmap	wormlooks = { /* For displaying centipede non-head segments.	*/
	(Word*) worm_bits,
	BLTWIDTH,
	{ { 0, 0 }, { 32, 32 } }
};

i4	head_bits[] = { /* What a centipede head segment looks like	*/
	0x00000000,
	0xF000000F,
	0xF800001F,
	0x1C07E038,
	0x0E3FF870,
	0x06FF7E60,
	0x03E60FE0,
	0x078903C0,
	0x0F01C9E0,
	0x3C000078,
	0x78F88F3E,
	0xE0FC1D8F,
	0xC1863EC3,
	0xC7037E63,
	0xC3017E63,
	0xD3077C6B,
	0xD31F7863,
	0xC31F4063,
	0xC7BF60E3,
	0xC5FE738B,
	0xC0FE3F03,
	0xC8781E03,
	0xE0028443,
	0x60C00413,
	0x70010027,
	0x380E3806,
	0x3D1E78CE,
	0x1E1E781C,
	0x070E387C,
	0x07E001F0,
	0x01FFFFE0,
	0x007FFF80
};

Bitmap	headlooks = { /* For displaying centipede head segments	*/
	(Word*) head_bits,
	BLTWIDTH,
	{ { 0, 0 }, { 32, 32 } }
};

struct	object	me = { {{0, 0}, {0, 0}},
		       {{0, 0}, {0, 0}}, 0, 0, 0, 0,
			personchoose,
			&melooks};
struct	object	slug = { {{0, 0}, {0, 0}},
			   {{0, 0}, {0, 0}}, 0, 0, 0, SLUGVALUE,
			slugchoose, &sluglooks};
struct	object	spider = { {{0, 0}, {0, 0}},
			   {{0, 0}, {0, 0}}, 0, 0, 0, SPIDERVALUE,
			spiderchoose, &spiderlooks};
struct	object	shot = { {{0, 0}, {0, 0}},
		       {{0, 0}, {0, 0}}, 0, SHOTSPEED, 0, 0,
			shotchoose, &shotlooks};
struct	object	scorpion = { {{0, 0}, {0, 0}},
		       {{0, 0}, {0, 0}}, 0, 0, 0, SCORPVALUE,
			scorpchoose, &scorplooks};
struct	object	worm[WORMMAX];	/* centipede objects	*/
char	glowmush[MUSHCOLS][MUSHROWS],/* TRUE at (x, y) if mush is glowing*/
	mushspace[MUSHCOLS][MUSHROWS],	/* number of chunks at scr. locs.*/
	spidbuf[4];	/* Score for last shot spider as shown on screen */
int	botmush_cnt,	/* Number of mushrooms at bottom of screen	*/
	firstworm,	/* The first existing centipede object	*/
	me_cnt,		/* No. of players remaining			*/
	mush_cnt, 	/* Number of mushrooms on screen		*/
	mushcols = MUSHCOLS,	/* Current # of columnss of mushrooms	*/
	mushrows = MUSHROWS,	/* Current # of rows of mushrooms	*/
	round_cnt,	/* Which Round of the game is it?	*/
	scorp_fuse,	/* countdown for next scorpion appearance	*/
	spider_fuse,	/* countdown for next spider appearance	*/
	start_over,	/* Start a new game?	*/
	topofbottom;	/* The top row in the player's region	*/
long	newmanat,	/* Score needed for next extra man	*/
	prevscore,	/* score to be updated from	*/
	score;		/* Score					*/
