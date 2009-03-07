.SUFFIXES: .isa .lst 

.isa.lst:
	./InsnList $< > $@
.isa.h:
	./isatobcg -m $< > $@

JAVAC = jikes +E # javac
YACCFLAGS = -d 		# FreeBSD make
YFLAGS = ${YACCFLAGS} 	# Needed on linux
# LEX =lex  -d 		# Pour debuggage token lexer
YACCFLAGS = -d -t 	# Pour debuggage token parser
FILESISA = isatobcg-p.o isatobcg-l.o common.o
CFLAGS = -Wall -g -I../common
TARGETS = \
	hpbcg-ia64.lst   hpbcg-ia64.h \
	hpbcg-cell.lst   hpbcg-cell.h \
	hpbcg-power4.lst hpbcg-power4.h
UTILS = hpbcg-cell-utils.h hpbcg-ia64-utils.h hpbcg-power4-utils.h hpbcg-asm-common.h

all: isatobcg ${TARGETS}

IsaToBCG: IsaToBCG.g
	antlr IsaToBCG.g
	${JAVAC} IsaToBCGParser.java IsaToBCGLexer.java InstructionsList.java Instruction.java InstructionBinPart.java

test: IsaToBCG
	java IsaToBCGParser < hpbcg-power4.isa 
#	java IsaToBCGParser < hpbcg-cell.isa 

debug: IsaToBCG
	java org.antlr.works.IDE IsaToBCG.g

isatobcg : ${FILESISA}
	${CC} ${CFLAGS} ${LDLIBS} ${FILESISA} -o $@

install: isatobcg
	../../CheckPrefix
	install -d ${PREFIX}/include/
	install ${TARGETS} ${PREFIX}/include/
	install ${UTILS} ${PREFIX}/include/

clean:
	-rm ${FILESISA}
	-rm ${TARGETS}
	-rm y.tab.h
