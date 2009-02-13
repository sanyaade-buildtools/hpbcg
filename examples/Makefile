DIR=simple-multiply rpn 
PROC=ia64 cell power4 matrix-vector
all:
	@echo "make what ?  [ ${PROC} ] "

clean:	
	(cd simple-multiply; 	make clean)
	(cd rpn; 		make clean)
	(cd matrix-vector;	make clean)

cell:
	(cd simple-multiply; 	make cell)
	(cd rpn; 		make cell)
	(cd matrix-vector;	make cell)

power4:
	(cd simple-multiply; 	make power4)
	(cd rpn; 		make power4)
	(cd matrix-vector;	make power4)

ia64:
	(cd simple-multiply; 	make ia64)
	(cd rpn; 		make ia64)
	(cd matrix-vector;	make ia64)
