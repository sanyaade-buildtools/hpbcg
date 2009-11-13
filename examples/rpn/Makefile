.SUFFIXES : .hg

.hg.c:
	hpbcg $< > $@

CFLAGS=-fno-inline -Winline -O3 -Wall -I${HPBCGHOME}/include/ -g ${ADDCFLAGS} # -DASM_DEBUG -DWITH_HPBCG_FUNCTIONS

CELLFILES =  rpn-cell.o main.o 
CDIR = /opt/cell/sdk/usr/
IAFILES =    rpn-ia64.o   main.o
POWERFILES = rpn-power4.o main.o
X86FILES =   rpn-x86.o    main.o
quoi:
	@echo -n "make what ?     "
	@echo "make [cell|ia64|power4|x86]"

all: ${FILES} rpn-${ARCH}

rpn-${ARCH}: ${FILES}
	${CC} ${CFLAGS} -o $@ ${FILES}

TestBuild : 
	${MAKE} clean
	${MAKE} MFLAGS="-n" x86
	${MAKE} MFLAGS="-n" ia64
	${MAKE} MFLAGS="-n" power4
	${MAKE} MFLAGS="-n" cell

cell: 
	${MAKE} ${MFLAGS} ARCH="cell" ADDCFLAGS="-I${CDIR}/include -lspe2" FILES="${CELLFILES}"  all
	${MAKE} ${MFLAGS} ARCH="cell" ADDCFLAGS="-I${CDIR}/include -lspe2" simple-worker-cell

simple-worker-cell:
	spu-gcc -I${CDIR}/include -g -o simple-worker-cell simple-worker-cell.c 

power4:
	${MAKE} ${MFLAGS} ARCH="$@" FILES="${POWERFILES}"  all

ia64:
	${MAKE} ${MFLAGS} ARCH="$@" FILES="${IAFILES}" all

x86:
	${MAKE} ${MFLAGS} ARCH="$@"  FILES="${X86FILES}" all

clean:
	${MAKE} ARCH="cell"   FILES="${CELLFILES}"  real-clean
	${MAKE} ARCH="ia64"   FILES="${IAFILES}"    real-clean
	${MAKE} ARCH="power4" FILES="${POWERFILES}" real-clean
	${MAKE} ARCH="x86"    FILES="${X86FILES}"   real-clean

real-clean:
	-rm ${FILES} rpn-${ARCH}.c rpn-${ARCH}
