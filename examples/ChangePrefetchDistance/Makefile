CFLAGS = -Wall -g
FILES = copyItaniumIcc.h ChangePrefetchDistance 

all:
	echo "x86 ou itanium"

itanium:
	${MAKE} MYOBJDUMP=objdump MYAS=as ${FILES}

x86:
	${MAKE} MYOBJDUMP=/usr/cross/ia64/usr/bin/objdump  MYAS=/usr/cross/ia64/usr/bin/as ${FILES}

copyItaniumIcc.h: copyItaniumIcc.s
	${MYAS} -o  copyItaniumIcc.o  copyItaniumIcc.s
	${MYOBJDUMP} -d copyItaniumIcc.o | ./objcopyToArray.awk > copyItaniumIcc.h

clean:
	-rm ${FILES}
	-rm copyItaniumIcc.h
