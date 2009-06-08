#include <stdio.h>
#include <stdlib.h>

#include "mandelbrot-common.h"

int isInSet(tComplex C, int limit, tReal moduleMax)
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
      mod = module (Z);
      //      pComplex(Z, stdout);
      if (moduleMax < mod) break;
    }
  //  (void) printf("%2.2f \n", mod);
  return i;
} /* isInSet */

int main(int argc, char * argv[])
{
  tComplex Center, C1, C2, Z;
  tReal reInc, imInc, reSize, imSize;
  int IMGXSIZE, IMGYSIZE, i, j, k;
  int COLORMAPSIZE = 65536;
  int ITERLIMIT = 256;
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
#ifdef WITHCOMPLEXSUPPORT
  fprintf(stderr, "Mendelbrot set (complex support): ");  pComplex(Center, stderr); 
#else 
  fprintf(stderr, "Mendelbrot set (real support): ");  pComplex(Center, stderr); 
#endif
  fprintf(stderr, "Size     : %2.2f %2.2f ", reSize, imSize);
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
	  printf("%d ", COLORMAPSIZE*isInSet(C2, ITERLIMIT, 4.0f)/ITERLIMIT);
	  RE(C2) += reInc;
	}
      IMAG(C1) += imInc;
      printf("\n");
    }
  return 0;
}
