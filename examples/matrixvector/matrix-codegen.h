/* Copyright (c) 2004 Henri-Pierre Charles. Tous droits reserves */

/***
   NOM
     matrix-ppc
   UTILITE
     
   NOTES
     $Revision: 1.2 $
     
   HISTOIRE
          hpc - Apr 19, 2004: Created.
     $Log: matrix-codegen.h,v $
     Revision 1.2  2004/05/06 14:32:01  kbrifa
     Mise au point de l'incrementation des loads.
     Prise en compte de la particularite de la fonction genMoveCst (int ou long).

     Revision 1.1  2004/04/21 12:00:23  hpc
     codegen pour sparc semble ok

     Revision 1.1  2004/04/19 16:36:15  hpc
     Début codegen

***/

#ifndef MATRIX_PPC
#define MATRIX_PPC

int regDst(int line);
int regSrc(int col);
int regMat(int line, int col);
int regIn(int narg);
int regBase(int narg);

void genAdd(int regD, int regSrc1, int regSrc2);
void genSub(int regD, int regSrc1, int regSrc2);
void genNeg(int regDst, int regSrc);
void genMul(int regD, int regMat, int regSrc);		/* r(regD) = r(regMat) * r(regSrc)  */
void genMulAdd(int regD, int regMat, int regSrc);	/* r(regD) = r(regD) + r(regMat) * r(regSrc)  */
void genLoad(int regD, int Depl, int regBase);		/* regD = [regBase + Depl]  */
void genStore(int regSrc, int Depl, int regBase);
void genMoveCst(int regDst, void *cst);			/* r(regDst) = cst */
void genMove(int regDst, int regSrc);			/* r(regDst) = r(regSrc) */
void genIncr(int regBase);

VectMatProd genNullMatProd();
VectMatProd Finalize();
void Initialize(int codeSize);
#endif /* MATRIX_PPC */








