.SUFFIXES : .tex .pdf

.tex.pdf:
	pdflatex $<
	bibtex 	`basename $< .tex`
	pdflatex $<
	pdflatex $<

all: images doc

images:
	(cd Img; ${MAKE})

doc: HPBCG.pdf


clean:
	(cd Img; ${MAKE} clean)
	-rm HPBCG.aux HPBCG.bbl HPBCG.blg HPBCG.log HPBCG.lot HPBCG.ps 
