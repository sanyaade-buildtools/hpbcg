.SUFFIXES : .class .java .g .hg

.hg.c:
	hpbcg $< > $@
.g.java:
	antlr $<
.java.class:
	${JAVAC} $<

JAVAC=jikes --emacs
JAVAC=javac # -target 4
JFILES = C.java Cell.java Ia64.java Power4.java X86.java
CFILES = Main.java Insn.java InsnCell.java InsnIa64.java  InsnPower4.java InsnList.java InsnX86.java
D = org/hpbcg

all: ${JFILES} class

class:
	${JAVAC} ${JFILES} ${CFILES} 

jar: all
	(cd ../.. ; jar cvfm HPBCG.jar ${D}/MonManifest.txt ${D}/*.g ${D}/*.class ${D}/*.java)

install: 
	../../../../CheckPrefix
	install -d ${PREFIX}/share/java
	install ../../HPBCG.jar ${PREFIX}/share/java
	install ../../antlr-3.1.1-runtime.jar ${PREFIX}/share/java
	install -d ${PREFIX}/bin
	sed "s?%%HOME%%?${PREFIX}?" ../../hpbcg.skel > ../../hpbcg
	install ../../hpbcg ${PREFIX}/bin
clean:
	-rm ${JFILES} *.class
	-rm *.tokens



