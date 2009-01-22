.SUFFIXES : .class .java .g

.g.java:
	antlr $<
.java.class:
	jikes --emacs $<


JFILES = C.java Cell.java 
CFILES = Main.java Insn.java InsnCell.java 
D = org/hpbcg
all: ${JFILES} class

class:
	jikes --emacs ${JFILES} ${CFILES} 

jar: all
	(cd ../.. ; jar cvfm HPBCG.jar ${D}/MonManifest.txt ${D}/*.g ${D}/*.class ${D}/*.java)

clean:
	-rm ${JFILES} *.class
	-rm *.tokens



