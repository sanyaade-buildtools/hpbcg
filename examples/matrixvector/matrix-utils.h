/* Copyright (c) 2004 Henri-Pierre Charles. Tous droits reserves */

/***
   NOM
     matrix-utils
   UTILITE
     
   NOTES
     $Revision: 1.1 $
     
   HISTOIRE
          hpc - Jan 12, 2004: Created.
     $Log: matrix-utils.h,v $
     Revision 1.1  2004/04/21 11:22:14  hpc
     Oubli matrix-utils.*

     Revision 1.2  2004/01/13 14:21:37  hpc
     ajouts asm-*.h

     Revision 1.1  2004/01/13 09:55:23  hpc
     Factorisation matrix-utils

***/

#ifndef MATRIX_UTILS
#define MATRIX_UTILS
#define T 4

typedef float Matrix[T][T];
typedef float Vector[T];

typedef void (*VectMatProd)(Vector, Vector);

void dotProduct(Matrix m, Vector src, Vector dest);
Matrix *readMatrix(char **values);
void printVector(Vector *v);
void printMatrix(Matrix *m);
void bkpt(void);
void tick(void);
unsigned long tock(void);

#endif /* MATRIX_UTILS */
