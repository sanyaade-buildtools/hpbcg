include ../../Makefile.conf

CFLAGS=-fno-inline -Winline -Wall -I${HPBCGHOME}/include/ -g ${ADDCFLAGS} # -DASM_DEBUG -DWITH_HPBCG_FUNCTIONS
CELLFILES =  rpn-cell.o 
IAFILES =    rpn-ia64.o   main.o
POWERFILES = rpn-power4.o main.o
X86FILES =   rpn-x86.o    main.o
ARMTHUMBFILES =   rpn-armthumb.o    main.o
quoi:
	@echo -n "make what ?     "
	@echo "make [cell|ia64|power4|x86|armthumb]"

all: ${FILES} rpn-${ARCH}

rpn-${ARCH}: ${FILES}
	${CC} ${CFLAGS} -o $@ ${FILES}

TestBuild : 
	${MAKE} clean
	${MAKE} MFLAGS="-n" x86
	${MAKE} MFLAGS="-n" ia64
	${MAKE} MFLAGS="-n" power4
	${MAKE} MFLAGS="-n" cell
	${MAKE} MFLAGS="-n" armthumb

cell: 
	${MAKE} ${MFLAGS} ARCH="cell" ADDCFLAGS="-lspe2" FILES="${CELLFILES}"  all
	${MAKE} ${MFLAGS} ARCH="cell" ADDCFLAGS="-lspe2" simple-worker-cell

simple-worker-cell:
	spu-gcc -I${CDIR}/include -g -o simple-worker-cell simple-worker-cell.c 

power4:
	${MAKE} ${MFLAGS} ARCH="$@" FILES="${POWERFILES}"  all

ia64:
	${MAKE} ${MFLAGS} ARCH="$@" FILES="${IAFILES}" all

x86:
	${MAKE} ${MFLAGS} ARCH="$@"  FILES="${X86FILES}" all

armthumb:
	${MAKE} ${MFLAGS} ARCH="$@"  FILES="${ARMTHUMBFILES}" ADDCFLAGS="-mthumb" all 

clean:
	${MAKE} ARCH="cell"     FILES="${CELLFILES}"  real-clean
	${MAKE} ARCH="ia64"     FILES="${IAFILES}"    real-clean
	${MAKE} ARCH="power4"   FILES="${POWERFILES}" real-clean
	${MAKE} ARCH="x86"      FILES="${X86FILES}"   real-clean
	${MAKE} ARCH="armthumb" FILES="${ARMTUMBCODE}"  real-clean

real-clean:
	-rm ${FILES} rpn-${ARCH}.c rpn-${ARCH}
