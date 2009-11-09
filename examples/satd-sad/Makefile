.SUFFIXES : .hg

.hg.c:
	hpbcg $< > $@

CFLAGS=-Wall -DARCH=${TARGET} -I${HPBCGHOME}/include/ -g ${ADDCFLAGS} # -DASM_DEBUG -DWITH_HPBCG_FUNCTIONS
CFILES = pixel-c.o timer.o
CELLFILES = 
CDIR = /opt/cell/sdk/usr/
IAFILES = 
POWERFILES = 
X86FILES = 
quoi:
	@echo -n "make what ?     "
	@echo "make [C]"

all: ${FILES}
	${CC} ${CFLAGS} -o test-pixel test-pixel.c ${FILES}

C:
	${MAKE} FILES="${CFILES}"  TARGET=C ADDCFLAGS="" all 
cell:
	${MAKE} FILES="${CELLFILES}"  ADDCFLAGS="-I${CDIR}/include -lspe2" all

simple-worker-cell: simple-worker-cell.c
	spu-gcc -I${CDIR}/include -g -o simple-worker-cell simple-worker-cell.c 

power4:
	${MAKE} FILES="${POWERFILES}"  all

ia64:
	${MAKE} FILES="${IAFILES}" all

x86:
	${MAKE} FILES="${X86FILES}" all

clean:
	${MAKE} FILES="${CFILES}"     real-clean

real-clean:
	-rm ${FILES}
