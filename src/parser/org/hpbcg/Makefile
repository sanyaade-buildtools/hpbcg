.SUFFIXES : .class .java .g .hg

.hg.c:
	hpbcg $< > $@
.g.java:
	antlr $<
.java.class:
	${JAVAC} $<

JAVAC=jikes --emacs
JAVAC=javac
JFILES = C.java Cell.java Ia64.java Power4.java
CFILES = Main.java Insn.java InsnCell.java InsnIa64.java  InsnPower4.java
D = org/hpbcg
all: ${JFILES} class

class:
	${JAVAC} ${JFILES} ${CFILES} 

jar: all
	(cd ../.. ; jar cvfm HPBCG.jar ${D}/MonManifest.txt ${D}/*.g ${D}/*.class ${D}/*.java)

clean:
	-rm ${JFILES} *.class
	-rm *.tokens



