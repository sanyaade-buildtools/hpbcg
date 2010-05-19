# Home makefile 

# WHERE = /usr/local

all:
	@echo "${MAKE} what [dist | install | build] ?"

dist: clean
	(cd ../; tar cvfzX HPBCG-`date +"%Y.%m.%d"`.tgz hpbcg/excludeList.txt hpbcg/*)

build:  clean
	${MAKE} -C src/isatobcg
	${MAKE} -C src/parser/org/hpbcg all
	@echo "Ready to install" 
	@echo "Launch make install WHERE=<Your dest dir>" 
	@echo "example make WHERE=/usr/local" 

install: 
	${MAKE} -C src/isatobcg install PREFIX=${WHERE}
	${MAKE} -C src/parser/org/hpbcg install PREFIX=${WHERE}
	@echo "-- You could/should define variables like (on csh)"
	@echo "setenv HPBCGHOME ${WHERE}"
	@echo "setenv PATH ${WHERE}/bin/:"'$${PATH}'
	@echo "-- or on sh/bash"
	@echo "export HPBCGHOME=${WHERE}"
	@echo "export PATH=${WHERE}/bin/:"'$${PATH}'

clean:
	${MAKE} -C docs clean
	${MAKE} -C src/isatobcg clean
	${MAKE} -C src/parser/org/hpbcg clean
	${MAKE} -C examples clean
