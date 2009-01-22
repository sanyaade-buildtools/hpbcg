.SUFFIXES: .isa .lst 

.isa.lst:
	./InsnList $< > $@
.isa.h:
	./isatobcg -m $< > $@

YACCFLAGS = -d 		# FreeBSD make
YFLAGS = ${YACCFLAGS} 	# Needed on linux
# LEX =lex  -d 		# Pour debuggage token lexer
YACCFLAGS = -d -t 	# Pour debuggage token parser
ISAFILES  = ia64.isa cellPTX.isa 
FILESISA = isatobcg-p.o isatobcg-l.o common.o
CFLAGS = -Wall -g -I../common
TARGETS = \
	ia64.lst ia64.h \
	cell.lst cell.h 

all: isatobcg ${TARGETS}

isatobcg : ${FILESISA}
	${CC} ${CFLAGS} ${LDLIBS} ${FILESISA} -o $@

install: isatobcg
	install -d ${PREFIX}/include/
	install ${TARGETS} ${PREFIX}/include/
clean:
	-rm ${FILESISA}
	-rm ${TARGETS}
	-rm y.tab.h
