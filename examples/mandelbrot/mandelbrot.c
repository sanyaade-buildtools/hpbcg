#include <stdio.h>
#include <stdlib.h>

typedef double tReal;

#ifdef WITHCOMPLEXSUPPORT
#include <complex.h>
#define tComplex _Complex double
#define RE(var)   __real__ (var)
#define IMAG(var) __imag__ (var)
void cSet(tComplex *a, tReal re, tReal im) { __real__ *a = re;  __imag__ *a = im; } 
tComplex cMul(tComplex a, tComplex b)	{ return a*b; 	} /* cMul */
tComplex cSub(tComplex a, tComplex b)	{ return a-b;   } /* cSub */
tComplex cAdd(tComplex a, tComplex b)   { return a+b;   } /* cAdd */
tReal module(tComplex a)
{
  tReal r = __real__ a;
  tReal i = __imag__ a;
  return a*a + i*i;
} /* module */

void pComplex(tComplex a, FILE *o)
{
  fprintf(o, "%+2.2f+i*%+2.2f ", __real__  a, __imag__ a);
} /* pComplex */
#else
typedef struct { tReal re, im; } tComplex;
#define RE(var)    (var).re
#define IMAG(var)  (var).im
void cSet(tComplex *a, tReal re, tReal im)	{ a->re = re; a->im = im;} 
tComplex cMul(tComplex a, tComplex b)
{
  tComplex tmp;
  tmp.re = a.re * b.re - a.im * b.im;
  tmp.im = a.re * b.im + a.im * b.re;
  return tmp;
} /* cMul */

tComplex cSub(tComplex a, tComplex b)
{
  tComplex tmp;
  tmp.re = a.re - b.re;
  tmp.im = a.im - b.im;
  return tmp;
} /* cSub */

tComplex cAdd(tComplex a, tComplex b)
{
  tComplex tmp;
  tmp.re = a.re + b.re;
  tmp.im = a.im + b.im;
  return tmp;
} /* cAdd */

tReal module(tComplex a)
{
  return a.re*a.re + a.im*a.im;
} /* module */


void pComplex(tComplex a, FILE *o)
{
  fprintf(o, "%+2.2f+i*%+2.2f ", a.re, a.im);
} /* pComplex */

#endif

int isInSet(tComplex C, int limit, int colorMapSize)
{
  int i;
  tReal mod;
#ifdef WITHCOMPLEXSUPPORT
  tComplex Z = 0.0fi + 0.0f;
#else
  tComplex Z = {0.0f, 0.0f};
#endif
  for (i = 0; i < limit; i++)
    {
      Z = cAdd (cMul (Z, Z), C);
      //  pComplex(Z, stdout);
      mod = module (Z);
      if (4.0 < mod) break;
    }
  return colorMapSize*i/limit;
} /* isInSet */

int main(int argc, char * argv[])
{
  tComplex Center, C1, C2, Z;
  tReal reInc, imInc, reSize, imSize;
  int IMGXSIZE, IMGYSIZE, i, j, k;
  int COLORMAPSIZE = 65536;
  if (argc <= 6)
    {
      fprintf(stderr, "%s [Cr] i[Ci] re[Size] i[Size] imgXsize imgYsize\n", argv[0]);
      fprintf(stderr, "C = Center, B = bottom rigth\n");
      exit(0);
    }
  cSet(&Center, atof (argv[1]), atof (argv[2]));
  reSize     = atof (argv[3]);  imSize   = atof (argv[4]);
  IMGXSIZE   = atoi (argv[5]);
  IMGYSIZE   = atoi (argv[6]);
  fprintf(stderr, "Mendelbrot set : ");  pComplex(Center, stderr); 
  fprintf(stderr, "\nSize     : %f %f \n", reSize, imSize);
  fprintf(stderr, "Img Size : %dx%d\n",IMGXSIZE, IMGYSIZE);

  reInc = reSize / IMGXSIZE;
  imInc = imSize / IMGYSIZE;
  cSet(&C1, RE(Center) - (reSize / 2.0f), IMAG(Center) - (imSize / 2.0f));
  (void) printf("P2\n");  
  (void) printf("%d %d\n", IMGXSIZE, IMGYSIZE);  
  (void) printf("%d\n", COLORMAPSIZE);  
  for (i = 0; i < IMGYSIZE; i++)
    {
      C2 = C1;
      for (j = 0; j < IMGXSIZE; ++j)
	{
	  printf("%d ", isInSet(C2, 256, COLORMAPSIZE));
	  RE(C2) += reInc;
	}
      IMAG(C1) += imInc;
      printf("\n");
    }
  return 0;
}
