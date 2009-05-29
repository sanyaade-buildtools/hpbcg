.SUFFIXES : .hg

.hg.c:
	hpbcg $< > $@

CFLAGS=-I${HPBCGHOME}/include/ -g ${ADDCFLAGS} # -DWITHCOMPLEXSUPPORT
FILES = mandelbrot
quoi:
	@echo -n "make what ?     "
	@echo "make [cell|ia64|power4|bluegene]"

all: ${FILES}

test: all
	time ./mandelbrot 0.0    0.0 3    3    1280 1024 > /tmp/OUT1.pgm
	time ./mandelbrot -1.411 0.0 0.01 0.01 1280 1024 > /tmp/OUT2.pgm
	qiv -T /tmp/OUT*.pgm&

clean:
	-rm ${FILES}


