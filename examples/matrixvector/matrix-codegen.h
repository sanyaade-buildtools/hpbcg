/* Copyright (c) 2004 Henri-Pierre Charles. Tous droits reserves */

/***
   NOM
     matrix-ppc

***/

#ifndef MATRIX_CODEGEN
#define MATRIX_CODEGEN

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
#endif /* MATRIX_CODEGEN */








