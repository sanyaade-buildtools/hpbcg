# Home makefile 

# WHERE = /usr/local

all:
	@echo "${MAKE} what [dist|install] ?"

dist: clean
	(cd ../; tar cvfz -X HPBCG/excludeList.txt HPBCG-`date +"%Y.%m.%d"`.tgz HPBCG/*)

build:  clean
	${MAKE} -C src/isatobcg
	${MAKE} -C src/parser/org/hpbcg jar

install: build
	${MAKE} -C src/isatobcg install PREFIX=${WHERE}
	${MAKE} -C src/parser/org/hpbcg install PREFIX=${WHERE}

clean:
	${MAKE} -C docs clean
	${MAKE} -C src/isatobcg clean
	${MAKE} -C src/parser/org/hpbcg clean
	${MAKE} -C examples clean
