

all:
	@echo "make what [dist] ?"

dist:
	(cd docs; make clean)
	(cd src/isatobcg; make clean)
	(cd src/parser/org/hpbcg; make clean)
	(cd examples; make clean)
	(cd ../; tar cvfz -X HPBCG/excludeList.txt HPBCG-`date +"%Y.%m.%d"`.tgz HPBCG/*)
