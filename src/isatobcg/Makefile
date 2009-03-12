.SUFFIXES: .isa .lst  .g .java .class

.isa.lst:
	./InsnList $< > $@
.isa.h:
	java IsaToBCGParser -m $< > $@
.g.java:
	antlr $<
	touch $@
.java.class:
	${JAVAC} $<

JAVAC = jikes +E # javac
JAVAC = javac
YACCFLAGS = -d 		# FreeBSD make
YFLAGS = ${YACCFLAGS} 	# Needed on linux
# LEX =lex  -d 		# Pour debuggage token lexer
YACCFLAGS = -d -t 	# Pour debuggage token parser
FILESISA = 
CFLAGS = -Wall -g -I../common
TARGETS = \
	hpbcg-cell.lst   hpbcg-cell.h 	\
	hpbcg-power4.lst hpbcg-power4.h \
	hpbcg-ia64.lst   hpbcg-ia64.h
UTILS = hpbcg-cell-utils.h hpbcg-ia64-utils.h hpbcg-power4-utils.h hpbcg-asm-common.h
CLASSFILES = IsaToBCGParser.class IsaToBCGLexer.class			\
InstructionsList.class Instruction.class InstructionBinPart.class

all: java isa

java: ${CLASSFILES}

isa: ${TARGETS}

IsaToBCGParser.java IsaToBCGLexer.java: IsaToBCG.java

debug: 
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
	-rm IsaToBCG*.class IsaToBCG*.java
	-rm ${CLASSFILES}