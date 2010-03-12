.SUFFIXES : .hg

.hg.c:
	hpbcg $< > $@

CDIR = /opt/cell/sdk/usr/
CFLAGS=-fno-inline -I${HPBCGHOME}/include/ -g ${ADDCFLAGS} 
LDFLAGS=${ADDLDFLAGS} 
CFILES       = mandelbrot-palette.h mandelbrot  
COMPLEXFILES = mandelbrot-palette.h mandelbrot-complex 
POWERFILES   = mandelbrot-palette.h mandelbrot-power4 mandelbrot-power4.c 
CELLFILES    = mandelbrot-palette.h mandelbrot-cell mandelbrot-cell.c simple-worker-cell
BGFILES      = mandelbrot-palette.h mandelbrot-bluegene mandelbrot-bluegene.c
IMGSIZE = 3000 3000
IMGFILE = "> /dev/null"
IMGSIZE = 8 8
IMGFILE = 
quoi:
	@echo -n "make what ?     "
	@echo "make [cell|ia64|power4|bluegene]"

all: ${FILES}

C:
	${MAKE} FILES="${CFILES}" ADDCFLAGS="-DtReal=double -Wall -O3" all
C-complex:
	${MAKE} FILES="${COMPLEXFILES}" ADDCFLAGS="-DtReal=double -Wall -O3 -DWITHCOMPLEXSUPPORT" all

power4:	# Could use  -DASM_DEBUG -DWITH_HPBCG_FUNCTIONS 
	${MAKE} FILES="${POWERFILES}" ADDCFLAGS="-DASM_DEBUG -DWITH_HPBCG_FUNCTIONS -DtReal=double -Wall " all

cell:	# Could use  -DASM_DEBUG -DWITH_HPBCG_FUNCTIONS 
	${MAKE} FILES="${CELLFILES}" ADDCFLAGS="-DASM_DEBUG -DWITH_HPBCG_FUNCTIONS -DtReal=float -Wall -I${CDIR}/include" ADDLDFLAGS="-lspe2" all

bluegene:	# Could use  -DASM_DEBUG -DWITH_HPBCG_FUNCTIONS 
	${MAKE} FILES="${BGFILES}" ADDCFLAGS="" all

mandelbrot-palette.h: mandelbrot-palette
	./mandelbrot-palette 16384 > mandelbrot-palette.h

simple-worker-cell: simple-worker-cell.c
	spu-gcc -g ${CFLAGS} -o simple-worker-cell simple-worker-cell.c 

test: C C-complex power4 cell
	${MAKE} test-arch ARCH=""
	${MAKE} test-arch ARCH="-power4"
	${MAKE} test-arch ARCH="-complex"
	${MAKE} test-arch ARCH="-cell"

test-arch:
	time ./mandelbrot${ARCH}  0.0   0.0 3    3    ${IMGSIZE} ${IMGFILE}
	time ./mandelbrot${ARCH} -1.411 0.0 0.01 0.01 ${IMGSIZE} ${IMGFILE}
clean:
	-rm mandelbrot-palette
	${MAKE} FILES="${CFILES}"       real-clean
	${MAKE} FILES="${POWERFILES}"   real-clean
	${MAKE} FILES="${COMPLEXFILES}" real-clean
	${MAKE} FILES="${BGFILES}"      real-clean
	${MAKE} FILES="${CELLFILES}"    real-clean

real-clean:
	-rm ${FILES}


