.SUFFIXES : .hg

.hg.c:
	${HPBCGHOME}/src/parser/hpbcg $< > $@

HPBCGHOME=../../
CFLAGS=-I${HPBCGHOME}/src/isatobcg/ -g ${ADDCFLAGS}
CDIR = /opt/cell/sdk/usr/
CELLFILES = simple-multiply-cell.c simple-multiply-cell simple-worker-cell
IAFILES = simple-multiply-ia64.c simple-multiply-ia64 
POWERFILES = simple-multiply-power4.c simple-multiply-power4

quoi:
	@echo -n "make what ?     "
	@echo "make [cell|ia64|power4]"

all: ${FILES}

cell:
	make FILES="${CELLFILES}" ADDCFLAGS="-I${CDIR}/include -lspe2" all

simple-worker-cell: simple-worker-cell.c
	spu-gcc -I${CDIR}/include -g -o simple-worker-cell simple-worker-cell.c 

ia64:
	make FILES="${IAFILES}" ADDCFLAGS="" all
#	make FILES="${IAFILES}" ADDCFLAGS="-DASM_DEBUG" all

power4:
	make FILES="${POWERFILES}" ADDCFLAGS="" all

clean:
	make FILES="${CELLFILES}"  real-clean
	make FILES="${IAFILES}"    real-clean
	make FILES="${POWERFILES}" real-clean

real-clean:
	-rm ${FILES}


