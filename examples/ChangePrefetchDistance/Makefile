CFLAGS = -Wall -g
FILES = copyItaniumIcc.h ChangePrefetchDistance 

all: ${FILES}

copyItaniumIcc.h: copyItaniumIcc.o
	/usr/cross/ia64/usr/bin/objdump -d copyItaniumIcc.o | ./objcopyToArray.awk > copyItaniumIcc.h

clean:
	-rm ${FILES}
	-rm copyItaniumIcc.h
