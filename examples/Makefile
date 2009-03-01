DIR=simple-multiply rpn 
PROC=ia64 cell power4 matrix-vector
all:
	@echo "make what ?  [ ${PROC} ] "

clean:	
	${MAKE} -C simple-multiply clean
	${MAKE} -C rpn clean
	${MAKE} -C matrixvector clean

cell:
	${MAKE} -C simple-multiply cell
	${MAKE} -C rpn cell
	${MAKE} -C matrixvector cell

power4:
	${MAKE} -C simple-multiply power4
	${MAKE} -C rpn power4
	${MAKE} -C matrixvector power4

ia64:
	${MAKE} -C simple-multiply ia64
	${MAKE} -C rpn ia64
	${MAKE} -C matrixvector ia64
