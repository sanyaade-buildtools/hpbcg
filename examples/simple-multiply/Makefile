.SUFFIXES : .hg

.hg.c:
	hpbcg $< > $@

CFLAGS=-I${HPBCGHOME}/include/ -g ${ADDCFLAGS}
CDIR = /opt/cell/sdk/usr/
CELLFILES     = simple-multiply-cell simple-worker-cell
IAFILES       = simple-multiply-ia64 
POWERFILES    = simple-multiply-power4
BLUEGENEFILES = simple-multiply-bluegene

quoi:
	@echo -n "make what ?     "
	@echo "make [cell|ia64|power4|bluegene]"

all: ${FILES}

cell:
	make FILES="${CELLFILES}" ADDCFLAGS="-Wall -I${CDIR}/include -lspe2" all
simple-multiply-cell.c: simple-multiply-cell.hg

simple-worker-cell: simple-worker-cell.c
	spu-gcc -I${CDIR}/include -g -o simple-worker-cell simple-worker-cell.c 

ia64:
	make FILES="${IAFILES}" ADDCFLAGS="-Wall " all
#	make FILES="${IAFILES}" ADDCFLAGS="-DASM_DEBUG" all
simple-multiply-ia64.c: simple-multiply-ia64.hg

power4:
	make FILES="${POWERFILES}" ADDCFLAGS="-Wall " all
simple-multiply-power4.c: simple-multiply-power4.hg

bluegene:
	make CC=mpixlc FILES="${BLUEGENEFILES}" ADDCFLAGS="" all
simple-multiply-bluegene.c : simple-multiply-bluegene.hg

clean:
	make FILES="${CELLFILES}"  real-clean
	make FILES="${IAFILES}"    real-clean
	make FILES="${POWERFILES}" real-clean

real-clean:
	-rm ${FILES}


