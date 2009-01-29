.SUFFIXES : .svg .pdf

.svg.pdf:
	inkscape --export-pdf=$@ $< # 
#	svg2pdf $< $@

FILES = IsaToHPBCGChain.pdf

all: ${FILES}


clean:
	-rm ${FILES}
