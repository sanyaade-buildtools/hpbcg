.SUFFIXES : .hg

.hg.c:
	hpbcg $< > $@

# HPBCGHOME=../../
CFLAGS=-Wall -I${HPBCGHOME}/include/ -g ${ADDCFLAGS} # -DASM_DEBUG -g -DWITH_HPBCG_FUNCTIONS
CDIR = /opt/cell/sdk/usr/
COMMON = matrix matrix-utils.o
POWERFILES = matrixvector-power4.c matrixvector-power4 ${COMMON}

quoi:
	@echo -n "make what ?     "
	@echo "make [power4]"

all: ${FILES}

power4:
	${MAKE} FILES="${POWERFILES}"  all

clean:
	${MAKE} FILES="${POWERFILES}" real-clean
#	 ${MAKE} FILES="${CELLFILES}" real-clean
#	 ${MAKE} FILES="${IAFILES}" real-clean

real-clean:
	-rm ${FILES}
