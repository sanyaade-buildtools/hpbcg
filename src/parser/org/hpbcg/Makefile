include ../../../../Makefile.conf

JFILES = C.java Cell.java Ia64.java Power4.java X86.java ArmThumb.java Debug.java 
CFILES = Main.java Insn.java InsnCell.java InsnIa64.java	\
InsnPower4.java InsnList.java InsnX86.java InsnArmThumb.java
D = org/hpbcg
JARFILES =  ../../HPBCG.jar

all: ${JFILES} class jar

class:
	${JAVAC} ${JFILES} ${CFILES} 

jar: 
	(cd ../.. ; ${JAR} cvfm ${D}/${JARFILES} ${D}/MonManifest.txt ${D}/*.g ${D}/*.class ${D}/*.java)

Debug.java:
	echo "package org.hpbcg; " 				> Debug.java
	echo "public class Debug " 				>> Debug.java
	echo "{" 						>> Debug.java
	awk -v ARCH=X86 -f ToDebug.awk X86.tokens 		>> Debug.java
	awk -v ARCH=Ia64 -f ToDebug.awk Ia64.tokens 		>> Debug.java
	awk -v ARCH=Power4 -f ToDebug.awk Power4.tokens 	>> Debug.java
	awk -v ARCH=Cell -f ToDebug.awk Cell.tokens 		>> Debug.java
	awk -v ARCH=ArmThumb -f ToDebug.awk ArmThumb.tokens 	>> Debug.java
	echo "}" 						>> Debug.java

install: 
	../../../../CheckPrefix
	install -d ${PREFIX}/share/java
	install ${JARFILES} ${PREFIX}/share/java
	install ../../antlr-3.1.1-runtime.jar ${PREFIX}/share/java
	install -d ${PREFIX}/bin
	sed "s?%%HOME%%?${PREFIX}?" ../../hpbcg.skel > ../../hpbcg
	install ../../hpbcg ${PREFIX}/bin
clean:
	-rm ${JFILES} *.class
	-rm *.tokens
	-rm ${JARFILES}
