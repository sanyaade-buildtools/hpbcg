# Home makefile 

# WHERE = /usr/local

all:
	@echo "make what [dist|install] ?"

dist:
	(cd docs; 		make clean)
	(cd src/isatobcg; 	make clean)
	(cd src/parser/org/hpbcg; make clean)
	(cd examples; 		make clean)
	(cd ../; tar cvfz -X HPBCG/excludeList.txt HPBCG-`date +"%Y.%m.%d"`.tgz HPBCG/*)

install: 
	(cd src/isatobcg; 	  make install PREFIX=${WHERE})
	(cd src/parser/org/hpbcg; make install PREFIX=${WHERE})
