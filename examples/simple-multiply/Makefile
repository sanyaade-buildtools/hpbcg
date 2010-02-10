include ../../Makefile.conf

CFLAGS=-I${HPBCGHOME}/include/ -g ${ADDCFLAGS}  -DASM_DEBUG=1 -DWITH_HPBCG_FUNCTIONS=1 
CFLAGS=-I${HPBCGHOME}/include/ -g ${ADDCFLAGS} # -DASM_DEBUG=1 -DWITH_HPBCG_FUNCTIONS=1 
CELLFILES     = simple-multiply-cell.o simple-worker-cell
IAFILES       = simple-multiply-ia64.o		main.o
POWERFILES    = simple-multiply-power4.o	main.o
BLUEGENEFILES = simple-multiply-bluegene.o	main.o
X86FILES      = simple-multiply-x86.o 		main.o

quoi:
	@echo -n "make what ?     "
	@echo "make [cell|ia64|power4|bluegene|x86]"

all: ${FILES} simple-multiply-${ARCH}

simple-multiply-${ARCH}: ${FILES}
	${CC} ${CFLAGS} -o $@ ${FILES}

cell:
	${MAKE} ${MFLAGS} FILES="${CELLFILES}" ADDCFLAGS="-Wall -lspe2" all
simple-multiply-cell.c: simple-multiply-cell.hg

simple-worker-cell: simple-worker-cell.c
	spu-gcc -g -o simple-worker-cell simple-worker-cell.c 

x86:
	${MAKE} ${MFLAGS} ARCH="$@" FILES="${X86FILES}" ADDCFLAGS="-Wall " all

ia64:
	${MAKE} ${MFLAGS} ARCH="$@" FILES="${IAFILES}" ADDCFLAGS="-Wall " all

power4:
	${MAKE} ${MFLAGS} ARCH="$@" FILES="${POWERFILES}" ADDCFLAGS="-Wall " all

bluegene:
	${MAKE} ${MFLAGS} CC=mpixlc FILES="${BLUEGENEFILES}" ADDCFLAGS="" all
simple-multiply-bluegene.c : simple-multiply-bluegene.hg

clean:
	${MAKE} ${MFLAGS} ARCH="cell"   FILES="${CELLFILES}"  real-clean
	${MAKE} ${MFLAGS} ARCH="ia64"   FILES="${IAFILES}"    real-clean
	${MAKE} ${MFLAGS} ARCH="power"  FILES="${POWERFILES}" real-clean
	${MAKE} ${MFLAGS} ARCH="x86"    FILES="${X86FILES}"   real-clean

real-clean:
	-rm ${FILES} simple-multiply-${ARCH}.c simple-multiply-${ARCH}
