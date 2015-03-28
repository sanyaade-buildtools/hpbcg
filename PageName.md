# HPBCG high performance binary code generation #

HPBCG is a tool which allow to generate binary code at run time without any compiler assembler. It currently can generate code for Itanium, power4 (bluegene version), cell and ARM

This tool is provided by Henri-Pierre Charles [mailto:hpc@prism.uvsq.fr](mailto:hpc@prism.uvsq.fr) or http://henripierre.charles.free.fr/

## Usage ##

HPBCG is useful in different situations :
  * Code specialization at run-time
  * Writing "compilettes". A "compilette" is define as a tiny compiler able to generate binary code at run-time. A "compilette" is able to :
    * Specialize code at run-time based on run time context (values, memory aligments, etc)
    * Use vector and multimedia instruction set
  * Mix data and instructions at run-time
## Articles / Talks ##

**2009
  * October During the '1ère Open Source Developers Conference France' http://act.osdc.fr/osdc2009fr/ [Slides (parts in french](http://henripierre.charles.free.fr/pmwiki/uploads/Rech/091002.Osdc.pdf)
  * March 6 : College Station Texas
    *** Parasol seminar http://parasol.tamu.edu/seminar/
    * **How to handle code [generation on modern processors architectures ? ](http://henripierre.charles.free.fr/pmwiki/uploads/Rech/090306.SlidesTamuHPCharles.pdf)**

## Licence ##

HPBCG is under CECILL-B licence (BSD like)