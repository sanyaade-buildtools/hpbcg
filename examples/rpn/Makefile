.SUFFIXES : .hg

.hg.c:
	hpbcg $< > $@

CFLAGS=-Wall -I${HPBCGHOME}/include/ -g ${ADDCFLAGS} -DASM_DEBUG -DWITH_HPBCG_FUNCTIONS

CELLFILES = rpn-cell.c rpn-cell simple-worker-cell
CDIR = /opt/cell/sdk/usr/
IAFILES = rpn-ia64.c rpn-ia64
POWERFILES = rpn-power4.c rpn-power4
quoi:
	@echo -n "make what ?     "
	@echo "make [cell|ia64|power4]"

all: ${FILES}

send: rpn-cell.c rpn-power4.c
	rsync -rv . turner:HPBCG/examples/rpn/

cell:
	make FILES="${CELLFILES}"  ADDCFLAGS="-I${CDIR}/include -lspe2" all

power4:
	make FILES="${POWERFILES}"  all

simple-worker-cell: simple-worker-cell.c
	spu-gcc -I${CDIR}/include -g -o simple-worker-cell simple-worker-cell.c 


ia64:
	make FILES="${IAFILES}" all

clean:
	make FILES="${CELLFILES}" real-clean
	make FILES="${IAFILES}" real-clean
	make FILES="${POWERFILES}" real-clean

real-clean:
	-rm ${FILES}
