CFLAGS = -g -O3 ${LDLIBS} ${ADDFLAGS}
LDLIBS =   
FILES = Experiment.o MyAdd.o

all:
	@echo "which arch ?"
	@echo "make armthumb"
	@echo "make x86"

armthumb:
	${MAKE} ADDFLAGS="-DARCH=arm -mthumb" Experiment
x86:
	${MAKE} ADDFLAGS="-DARCH=x86"  Experiment

Experiment: ${FILES}
	${CC} ${CFLAGS} ${LDLIBS} -o $@ ${FILES}
clean:
	-rm ${FILES} Experiment

