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
	cleantex -a HPBCG.tex
	-rm HPBCG.pdf
