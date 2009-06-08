.SUFFIXES : .hg

.hg.c:
	hpbcg $< > $@

CFLAGS=-fno-inline -I${HPBCGHOME}/include/ -g ${ADDCFLAGS} 
CFILES       = mandelbrot
COMPLEXFILES = mandelbrot-complex
POWERFILES   = mandelbrot-power4 mandelbrot-power4.c
CELLFILES   = mandelbrot-cell4 mandelbrot-cell4.c
BGFILES   = mandelbrot-bluegene mandelbrot-bluegene.c
FILES  = 
IMGSIZE = 3000 3000

quoi:
	@echo -n "make what ?     "
	@echo "make [cell|ia64|power4|bluegene]"

all: C C-complex power4 

C:
	${MAKE} ADDCFLAGS="-O3" mandelbrot
C-complex:
	${MAKE} ADDCFLAGS="-O3 -DWITHCOMPLEXSUPPORT" mandelbrot-complex

power4:	# Could use  -DASM_DEBUG -DWITH_HPBCG_FUNCTIONS 
	${MAKE} ADDCFLAGS="" mandelbrot-power4

cell:	# Could use  -DASM_DEBUG -DWITH_HPBCG_FUNCTIONS 
	${MAKE} ADDCFLAGS="" mandelbrot-cell

bluegene:	# Could use  -DASM_DEBUG -DWITH_HPBCG_FUNCTIONS 
	${MAKE} ADDCFLAGS="" mandelbrot-bluegene

mandelbrot-complex: mandelbrot.c
	${CC} ${CFLAGS} -o $@ $?

mandelbrot-power4: mandelbrot-power4.c
mandelbrot-power4.c: mandelbrot-power4.hg
mandelbrot-cell: mandelbrot-cell.c
mandelbrot-cell.c: mandelbrot-cell.hg

test: all
	make test-arch ARCH=""
	make test-arch ARCH="-power4"
	make test-arch ARCH="-cell"
	make test-arch ARCH="-complex"
	scp /tmp/OUT[12]*.pgm vlaminck:/usr/tmp

test-arch:
	time ./mandelbrot${ARCH}  0.0   0.0 3    3    ${IMGSIZE} > /dev/null
	time ./mandelbrot${ARCH} -1.411 0.0 0.01 0.01 ${IMGSIZE} > /dev/null
clean:
	make FILES="${CFILES}"       real-clean
	make FILES="${POWERFILES}"   real-clean
	make FILES="${COMPLEXFILES}" real-clean
	make FILES="${BGFILES}"      real-clean
	make FILES="${CELLILES}"     real-clean

real-clean:
	-rm ${FILES}


