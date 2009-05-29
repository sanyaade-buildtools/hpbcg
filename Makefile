# Home makefile 

# WHERE = /usr/local

all:
	@echo "${MAKE} what [dist | install | build] ?"

dist: clean
	(cd ../; tar cvfzX HPBCG-`date +"%Y.%m.%d"`.tgz HPBCG/excludeList.txt HPBCG/*)

build:  clean
	${MAKE} -C src/isatobcg
	${MAKE} -C src/parser/org/hpbcg jar

install: 
	${MAKE} -C src/isatobcg install PREFIX=${WHERE}
	${MAKE} -C src/parser/org/hpbcg install PREFIX=${WHERE}

clean:
	${MAKE} -C docs clean
	${MAKE} -C src/isatobcg clean
	${MAKE} -C src/parser/org/hpbcg clean
	${MAKE} -C examples clean
