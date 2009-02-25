/* Copyright (c) 2004 Henri-Pierre Charles. Tous droits reserves */

/***
   NOM
     matrix-utils
***/

#include <stdio.h>
#include <stdlib.h>

#include "matrix-utils.h"


/*** static dot product ***/

void dotProduct(Matrix m, Vector src, Vector dest)
{
#if 0		/* this is SOMEWHAT unfair! */
  int i;
  for (i= 0;  i < T;  ++i)
    {
      int j;
      dest[i]= 0;
      for (j= 0;  j < T;  ++j)
	dest[i] += src[j] * m[i][j];
    }
#else	/*  let's unroll the loops to match the dynamic case... */
  {
    dest[0]= src[0] * m[0][0]  +  src[1] * m[0][1]  +  src[2] * m[0][2]  +  src[3] * m[0][3];
    dest[1]= src[0] * m[1][0]  +  src[1] * m[1][1]  +  src[2] * m[1][2]  +  src[3] * m[1][3];
    dest[2]= src[0] * m[2][0]  +  src[1] * m[2][1]  +  src[2] * m[2][2]  +  src[3] * m[2][3];
    dest[3]= src[0] * m[3][0]  +  src[1] * m[3][1]  +  src[2] * m[3][2]  +  src[3] * m[3][3];
  }
#endif
}


/* read a 4x4 matrix */

Matrix *readMatrix(char **values)
{
  int i, j, k;
  Matrix *p;

  p= (Matrix *)calloc(1, sizeof (Matrix));
  if (!p)
    {
      fprintf(stderr, "out of memory\n");
      exit(1);
    }

  k= 0;
  for (i= 0;  i < 4;  ++i)
    for (j= 0;  j < 4;  ++j)
      (*p)[i][j]= atof(values[k++]);

  return p;
}


void printVector(Vector *v)
{
  int i;
  for (i= 0;  i < T;  ++i)
    printf("%f ", (*v)[i]);
  printf("\n");
}

void printMatrix(Matrix *m)
{
  int i, j;
  for (i= 0;  i < T;  ++i)
    {
      for (j= 0;  j < T;  ++j)
	printf("%f ", (*m)[i][j]);
      printf("\n");
    }
}

void bkpt(void) { /* debugger breakpoint */ }

/*** timing ***/
#include <sys/time.h>
#include <sys/resource.h>

struct rusage tickTime;

void tick(void)
{
  if (getrusage(RUSAGE_SELF, &tickTime))
    perror("getrusage");
  return;
}

unsigned long tock(void)	/* user uSecs since last tick() */
{
  struct rusage tockTime;

  if (getrusage(RUSAGE_SELF, &tockTime))
    perror("getrusage");

  return (( (tockTime.ru_utime.tv_sec * 1000000 + tockTime.ru_utime.tv_usec))
	  - (tickTime.ru_utime.tv_sec * 1000000 + tickTime.ru_utime.tv_usec));
}


