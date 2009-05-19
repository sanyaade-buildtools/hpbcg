.SUFFIXES : .hg

.hg.c:
	hpbcg $< > $@

CFLAGS=-I${HPBCGHOME}/include/ -g ${ADDCFLAGS}
CDIR = /opt/cell/sdk/usr/
FILES = mandelbrot
quoi:
	@echo -n "make what ?     "
	@echo "make [cell|ia64|power4|bluegene]"

all: ${FILES}

test: all
	./mandelbrot -1.411 0.0  0.01 0.01 640 480 > OUT.pgm
	qiv -T OUT.pgm&

clean:
	make FILES="${CELLFILES}"  real-clean
	make FILES="${IAFILES}"    real-clean
	make FILES="${POWERFILES}" real-clean

real-clean:
	-rm ${FILES}


