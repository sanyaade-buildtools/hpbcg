.SUFFIXES : .tex .pdf

.tex.pdf:
	pdflatex $<
	bibtex 	`basename $< .tex`
	pdflatex $<
	pdflatex $<

all: images doc

images:
	(cd Img; make)

doc: HPBCG.pdf


clean:
	(cd Img; make clean)
	-rm HPBCG.aux HPBCG.bbl HPBCG.blg HPBCG.log HPBCG.lot HPBCG.ps 
