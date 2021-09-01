
#
#      Copyright (c) 1984, 1985 AT&T
#      All Rights Reserved
#
#      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
#      CODE OF AT&T.
#      The copyright notice above does not 
#      evidence any actual or intended
#      publication of such source code.
#
#
#	'Makefile' for CENTIPEDE by Pat Autilio	11/3/83
#

# -DBUMPMUSH doesn't work yet

CFLAGS	=	-O

DMD	= /phx3/dmd1.1
DMDBIN	= $(DMD)/bin
DMDSGS	= $(DMD)/sgs/1.0ofc
DMDCC	= $(DMDBIN)/dmdcc
DMDINCLUDE	= $(DMD)/include
DMDFLAGS	= -I$(DMDINCLUDE) $(CFLAGS)

DLIB	=	cent.dmd.a

CC	=	$(DMDCC)

.SUFFIXES: .b
JERQ	=	/usr/jerq
JERQINCLUDE	=	$(JERQ)/include
JERQBIN	=	$(JERQ)/bin
JERQFLAGS	=  -I$(JERQINCLUDE) -Dmc68000 $(CFLAGS)
#
JERQCC	=	$(JERQBIN)/mcc

CFILES =	chk_coll.c chk_mecoll.c digits.c error.c exit_game.c\
		globals.c init_game.c init_round.c init_scr.c\
		killplayer.c objXobj.c perchoose.c playdisp.c player.c\
		put_chunk.c scochoose.c srvmouse.c shotchoose.c\
		slugchoose.c spichoose.c start.c wormchoose.c
BFILES =	chk_coll.b chk_mecoll.b digits.b error.b exit_game.b\
		globals.b init_game.b init_round.b init_scr.b\
		killplayer.b objXobj.c perchoose.b playdisp.b player.b\
		put_chunk.b scochoose.b srvmouse.b shotchoose.b\
		slugchoose.b spichoose.b start.b wormchoose.b
SRCFILES =	cent.6 cent.README Makefile playdefs.h $(CFILES)
#
# 'make' is all you have to make for this to work.
#
all: cent.dmd.m cent.jerq.m

dmd: cent.dmd.m

jerq: cent.jerq.m

cent.dmd.m: $(DLIB)
	DMDSGS=$(DMDSGS) DMD=$(DMD) $(DMDCC) -o cent.dmd.m $(DLIB)
	chmod 0755 cent.dmd.m

.PRECIOUS: $(DLIB)

$(DLIB):: \
		$(DLIB)(chk_coll.o)	\
		$(DLIB)(chk_mecoll.o)	\
		$(DLIB)(digits.o)	\
		$(DLIB)(error.o)	\
		$(DLIB)(exit_game.o)	\
		$(DLIB)(globals.o)	\
		$(DLIB)(init_game.o)	\
		$(DLIB)(init_round.o)	\
		$(DLIB)(init_scr.o)	\
		$(DLIB)(killplayer.o)	\
		$(DLIB)(objXobj.o)	\
		$(DLIB)(perchoose.o)	\
		$(DLIB)(playdisp.o)	\
		$(DLIB)(player.o)	\
		$(DLIB)(put_chunk.o)	\
		$(DLIB)(scochoose.o)	\
		$(DLIB)(srvmouse.o)	\
		$(DLIB)(shotchoose.o)	\
		$(DLIB)(slugchoose.o)	\
		$(DLIB)(spichoose.o)	\
		$(DLIB)(start.o)	\
		$(DLIB)(wormchoose.o)
	DMDSGS=$(DMDSGS) DMD=$(DMD) $(DMDCC) -c $(DMDFLAGS) $(?:.o=.c)
	ar5.0 rvu $(DLIB) $?
	rm $?

.c.a:;

cent.jerq.m: $(BFILES)
	$(JERQCC) -o cent.jerq.m $(BFILES)
	chmod 0755 cent.jerq.m

.c.b: playdefs.h
	$(JERQCC) $(JERQFLAGS) -c $<
	mv $*.o $*.b

#
# 'make print' will print all source on the local line printer.
#
print:
	pr -n $(SRCFILES) | opr -fstandard
#
# 'make xprint' will print all source on a xerox printer if
#	available.
#
xprint:
	pr -n $(SRCFILES) | opr -txr -pland -fhole

shrink:
	-rm -f *.b $(DLIB)
#
# 'make cpio' packs the source up for sending it somewhere.
#
cpio:
	ls $(SRCFILES) | cpio -oc > cent.cpio
#
# End of 'Makefile'
#
