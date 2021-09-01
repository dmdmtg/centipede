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

/* 'scorp_collision' checks to see if the scorpion gets hit or hit a
 *	mushroom.
 */
scorp_collision()
{
	int	i, j, k;
	
	i = mushx(scorpion.rect.origin.x);
	j = mushy(scorpion.rect.origin.y);
	if (mushspace[i][j] > 0) {
		for (k = 1; k <= mushspace[i][j]; k++)
			put_chunk (k, i, j);
		glowmush[i][j] = TRUE;
		for (k = 1; k <= mushspace[i][j]; k++)
			put_chunk (k, i, j);
	}
}

/* 'shot_collision' checks to see if the player's missile hit anything
 */
shot_collision()
{
	int	i, mx, my;
		
	if (!(ptinrect (shot.rect.origin, Drect))) {
		CLEAR_ATT (shot, EXISTS);
		put_object (shot);
		return (FALSE);
	}

	/* Check for shot */
	if (rectXrect (shot.rect, spider.rect) && IS_SET(spider, EXISTS)) {
		killspider ();
		return;
	}
	if (rectXrect (shot.rect, scorpion.rect) && IS_SET (scorpion, EXISTS)) {
		killscorp ();
		return;
	}
	if (rectXrect (shot.rect, slug.rect) && IS_SET (slug, EXISTS)) {
		killslug ();
		return;
	}

	mx = mushx(shot.rect.origin.x);
	my = mushy(shot.rect.origin.y);
	for (i = 0; i < WORMMAX; i++) {
		if (rectXrect (worm[i].rect, shot.rect) &&
		    IS_SET(worm[i], EXISTS)) {
			killworm(i, mx, my);
			return;
		}
	}
	/* Shot hit mushroom */
	if (mushspace[mx][my] > 0) {
		put_chunk (mushspace[mx][my], mx, my);
		mushspace[mx][my]--;
		if (mushspace[mx][my] == 0) {
			glowmush[mx][my] = FALSE;
			mush_cnt--;
			score += MUSHVALUE;
			disp_score();
			if (ptinrect (shot.rect.origin, botrect))
				botmush_cnt--;
		}
		CLEAR_ATT (shot, EXISTS);
		put_object (shot);
	}
}

/* 'slug_collision' checks to see if the mushroom dropper hits
 *	anything important.
 */
slug_collision()
{
	register int	mx, my,
			i;
			
	if (urnd (0, 8) < 1) {
		for (i = 0; i < WORMMAX; i++) {
			if (ptinrect (slug.rect.origin, worm[i].rect))
				return;
		}
		mx = mushx (slug.rect.origin.x);
		my = mushy (slug.rect.origin.y);
		if (mushspace[mx][my] == 0 && my < mushrows-1) {
			mush_cnt++;
			if (my >= topofbottom)
				botmush_cnt++;
			glowmush[mx][my] = FALSE;
			bitblt (&mushlooks,mushlooks.rect,&display,
				mushorigin(mx, my), F_XOR);
			mushspace[mx][my] = CHUNKMAX;
		}
	}
}

/* 'spid_collision' checks to see if the spider bumped into anything.
 */
spid_collision()
{
	register int	i, j, k;
			
	/* Check for bumped mushroom */
	i = mushx(div2(spider.rect.corner.x + spider.rect.origin.x));
	j = mushy(div2(spider.rect.corner.y + spider.rect.origin.y));
	if (mushspace[i][j] > 0) {
		for (k = 1; k <= mushspace[i][j]; k++) {
			put_chunk (k, i, j);
		}
		mushspace[i][j] = 0;
		glowmush[i][j] = FALSE;
		mush_cnt--;
		botmush_cnt--;
	}
}

/* 'worm_collision' check to see if centipede segment 'i' has hit the
 *	player or has been hit by the player's missile.
 */
worm_collision(i)
int	i;
{
	/* Nothing right now */
}

/* 'killscorp' does bookkeeping for when a scorpion is hit by player's
 *	missile.
 */
killscorp ()
{
	score += scorpion.value;
	disp_score();
	put_object (scorpion);
	CLEAR_ATT (shot, EXISTS);
	CLEAR_ATT (scorpion, EXISTS);
	put_object (shot);
	scorp_fuse = scorpgone ();
}

/* 'killslug' gets rid of the mushroom dropper.
 */
killslug()
{
	put_object(shot);
	CLEAR_ATT (shot, EXISTS);
	if (slug.dydt == SLOWSLUG) {
		slug.dydt = FASTSLUG;
	}
	else {
		score += slug.value;
		disp_score();
		put_object (slug);
		CLEAR_ATT (slug, EXISTS);
	}
}

/* 'killspider' removes the spider from the screen (for the time being).
 */
killspider ()
{
	int	i,
		spiddist,
		spidscore;
	
	spiddist = me.rect.origin.y - spider.rect.origin.y;
	put_object (spider);
	if (spiddist > 112)
		spidscore = spider.value;
	else if (spiddist > 48)
		spidscore = spider.value * 2;
	else {
		spidscore = spider.value * 3;
		if (mush_cnt == 0) /* facelooks */
			spider.looks = &facelooks;
	}
	score += spidscore;
	for (i = 2; i >= 0; i--) {
		spidbuf[i] = spidscore % 10 + '0';
		spidscore /= 10;
	}
	string (&defont, spidbuf, &display, spider.rect.origin, F_XOR);
	disp_score ();
	spider_fuse = SPIDERGONE;
	CLEAR_ATT (shot, EXISTS);
	CLEAR_ATT (spider, EXISTS);
	put_object (shot);
}

/* 'killworm' handles bookkeepping for when a centipede segment is shot.
 */
killworm (i, mx, my)
int	i,
	mx,
	my;
{
	if (i > 0 && IS_SET (worm[i-1], EXISTS)) {
		put_object (worm[i-1]);
		worm[i-1].looks = &headlooks;
		put_object (worm[i-1]);
		SET_ATT (worm[i-1], IS_HEAD);
	}
	if (IS_SET (worm[i], IS_HEAD))
		score += HEADVALUE;
	else
		score += WORMVALUE;
	disp_score();
	put_object (worm[i]);
	if (mushspace[mx][my] == 0) {
		mushspace[mx][my] = CHUNKMAX;
		mush_cnt++;
		if (my >= topofbottom)
			botmush_cnt++;
		glowmush[mx][my] = FALSE;
		bitblt (&mushlooks, mushlooks.rect, &display,
			mushorigin(mx, my), F_XOR);
	}
	CLEAR_ATT (shot, EXISTS);
	CLEAR_ATT (worm[i], EXISTS);
	put_object (shot);
}
