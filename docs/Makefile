.SUFFIXES : .tex .pdf

.tex.pdf:
	pdflatex $<
	pdflatex $<
	bibtex 	`basename $< .tex`
	pdflatex $<

all: images doc

images:
	(cd Img; make)

doc: HPBCG.pdf


clean:
	(cd Img; make clean)
	cleantex -a HPBCG.tex

