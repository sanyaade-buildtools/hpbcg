HPBCG is a tool which help to build binary code generator. It can be use for writing "compilettes" which are small compiler embedded into the application. It is usefull for

  * Dynamically adapt binary code at run-time
  * Dynamically generate an optimized function using
    * Vectorized instructions set
    * Multimedia instructions set

HPBCG is able to geneate binary code for the following platforms :

  * cell-spu : the vector unit of the cell platform (the code is generated on the PPU part)
  * itanium : the full instruction set is supported but HPBCG is not yet able to schedule instructions.
  * power4 : with altivec extensions and powerFP2 extensions (bluegene processor)

HPBCG is released on the CECILL-B licence, without any garantee