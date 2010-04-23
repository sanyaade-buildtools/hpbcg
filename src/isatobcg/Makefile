include ../../Makefile.conf

YACCFLAGS = -d 		# FreeBSD make
YFLAGS = ${YACCFLAGS} 	# Needed on linux
# LEX =lex  -d 		# Pour debuggage token lexer
YACCFLAGS = -d -t 	# Pour debuggage token parser
CFLAGS = -Wall -g -I../common
CLASSFILES = IsaToBCGParser.class IsaToBCGLexer.class	\
	Instruction.class InstructionBinPart.class	\
	InstructionAsmPart.class
CPU=armthumb cell power4 x86 ia64

all: ${CLASSFILES} ${CPU}

${CPU}: ${CLASSFILES} 
	make doth ARCH=$@
	make lst  ARCH=$@
	make test ARCH=$@

doth: ${CLASSFILES} hpbcg-${ARCH}.h

lst:  ${CLASSFILES} hpbcg-${ARCH}.lst

test: ${CLASSFILES} hpbcg-${ARCH}.testV hpbcg-${ARCH}.testE hpbcg-${ARCH}.testC

hpbcg-${ARCH}.testV:
	java IsaToBCGParser -v hpbcg-${ARCH}.isa
	touch hpbcg-${ARCH}.testV 

hpbcg-${ARCH}.testE:
	gcc -Wall -I. -E hpbcg-${ARCH}.h -o /dev/null 
	touch hpbcg-${ARCH}.testE

hpbcg-${ARCH}.testC:
	gcc -Wall -I. -c hpbcg-${ARCH}.h -o /dev/null 
	touch hpbcg-${ARCH}.testC

install:
	../../CheckPrefix
	install -d ${PREFIX}/include/
	install hpbcg-asm-common.h ${PREFIX}/include/
	${MAKE} installArch  ARCH=cell
	${MAKE} installArch  ARCH=power4
	${MAKE} installArch  ARCH=ia64
	${MAKE} installArch  ARCH=x86
	${MAKE} installArch  ARCH=armthumb

installArch:
	install hpbcg-${ARCH}.h hpbcg-${ARCH}.lst hpbcg-${ARCH}-utils.h ${PREFIX}/include/

# # Dummy rule 
IsaToBCGParser.java IsaToBCGLexer.java: IsaToBCG.java

clean: 
	-rm IsaToBCG*.class IsaToBCG*.java IsaToBCG.tokens
	-rm ${CLASSFILES}
	${MAKE} realclean  ARCH=cell
	${MAKE} realclean  ARCH=power4
	${MAKE} realclean  ARCH=ia64
	${MAKE} realclean  ARCH=x86
	${MAKE} realclean  ARCH=armthumb

realclean:
	-rm hpbcg-${ARCH}.h hpbcg-${ARCH}.lst
	-rm hpbcg-${ARCH}.testV hpbcg-${ARCH}.testE hpbcg-${ARCH}.testC
# debug: 
# 	java org.antlr.works.IDE IsaToBCG.g

# install: 
# 	../../CheckPrefix
# 	install -d ${PREFIX}/include/
# 	install ${TARGETS} ${PREFIX}/include/
# 	install ${UTILS} ${PREFIX}/include/
# test: test-v test-e test-c

