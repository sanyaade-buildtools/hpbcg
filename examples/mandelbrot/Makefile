.SUFFIXES : .hg

.hg.c:
	hpbcg $< > $@

CFLAGS=-I${HPBCGHOME}/include/ -g ${ADDCFLAGS} # -DASM_DEBUG -DWITH_HPBCG_FUNCTIONS # -DWITHCOMPLEXSUPPORT
CFILES = mandelbrot
POWERFILES = mandelbrot-power4 mandelbrot-power4.c
quoi:
	@echo -n "make what ?     "
	@echo "make [cell|ia64|power4|bluegene]"

all: ${FILES}

power4:
	hpbcg mandelbrot-power4.hg > mandelbrot-power4.c
	${CC} ${CFLAGS} -o mandelbrot-power4 mandelbrot-power4.c
test: all
	time ./mandelbrot 0.0    0.0 3    3    1280 1024 > /tmp/OUT1.pgm
	time ./mandelbrot -1.411 0.0 0.01 0.01 1280 1024 > /tmp/OUT2.pgm
	qiv -T /tmp/OUT*.pgm&

clean:
	make FILES="${CFILES}" real-clean
	make FILES="${POWERFILES}" real-clean

real-clean:
	-rm ${FILES}


