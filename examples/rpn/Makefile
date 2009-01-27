.SUFFIXES : .hg

.hg.c:
	../../src/parser/hpbcg $< > $@

HPBCGHOME=${HOME}/Travail/Prog/HPBCG/src
CFLAGS=-I${HPBCGHOME}/isatobcg/


quoi:
	@echo -n "make what ?     "
	@echo "make [cell|ia64]"

all: ${FILES}

cell:
	make FILES="rpn-cell.c rpn-cell" all

ia64:
	make FILES="rpn-ia64.c rpn-ia64" all

clean:
	make FILES="rpn-cell.c rpn-cell" real-clean
	make FILES="rpn-ia64.c rpn-ia64" real-clean

real-clean:
	-rm ${FILES}


