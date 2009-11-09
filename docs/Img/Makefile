.SUFFIXES : .svg .pdf

.svg.pdf:
	svg2pdf $< $@
#	inkscape --export-pdf=$@ $< # 


FILES = IsaToHPBCGChain.pdf FXCPMADD.pdf FXCXNPMA.pdf

all: ${FILES}


clean:
	-rm ${FILES}
