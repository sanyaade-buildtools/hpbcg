#include <stdio.h>
#include <stdlib.h>


typedef struct {int r, v, b;} tColor;

tColor BLACK = {  0,   0,   0};
tColor WHITE = {255, 255, 255};
tColor RED   = {255,   0,   0};
tColor GREEN = {0,   255,   0};
tColor BLUE  = {0,   0,   255};

void pPixel(tColor c)
{
#ifdef IMAGE
  printf("%d %d %d\n", c.r, c.v, c.b);
#else
  printf("{%d, %d, %d},\n", c.r, c.v, c.b);
#endif
} /* pColor */

void genDegrade(int l, tColor start, tColor end)
{
  float rDelta, vDelta, bDelta;
  int i;
  tColor tmp; 

  rDelta = (float) (end.r - start.r) / l;
  vDelta = (float) (end.v - start.v) / l;
  bDelta = (float) (end.b - start.b) / l;
  for (i = 0; i < l; ++i)
    {
      tmp.r = (int)(start.r + (float) i*rDelta); 
      tmp.v = (int)(start.v + (float) i*vDelta); 
      tmp.b = (int)(start.b + (float) i*bDelta); 
      pPixel(tmp);
    }
} /* genDegrage */


void genOneColor(int len, tColor theColor)
{
  printf("# Black to Color\n");
  genDegrade(len/4,   BLACK,    theColor);
  printf("# Color to white\n");
  genDegrade(len/4,   theColor, WHITE);
  printf("# White to color\n");
  genDegrade(len/4,   WHITE,    theColor);
  printf("# Color to black\n");
  genDegrade(len/4,   theColor, BLACK);
}

void genImage (int width, int height)
{
  int i, j, tmp;
  printf("P3\n");
  printf("%d %d\n", width, height);
  printf("%d \n", 256);
  for (i = 0; i < height; ++i)
    {
      (void) printf("# Beginning of line\n");
      genOneColor(width/4, BLUE);
      genOneColor(width/4, RED);
      genOneColor(width/4, GREEN);
      genOneColor(width/4, BLUE);
    }
} /* genImage */

void genColorMap(int width)
{
  int i, tmp;
  printf("#define COLORMAPSIZE %d\n", width);
  printf("typedef struct {int r, v, b;}tColor;\n");
  printf("tColor thePalette[%d]=\n", width);
  printf("{\n");
  genOneColor(width/4, RED);
  genOneColor(width/4, GREEN);
  genOneColor(width/4, BLUE);
  genOneColor(width/4, BLUE);
  printf("};\n");
} /* GenColorMap */

int main(int argc, char * argv[])
{
  int lenght, i, bitcount;

  if (argc < 2)
    {
      printf("%s Lenght\n", argv[0]);
      exit(0);
    }
  lenght = atoi(argv[1]);
  for (bitcount = 0, i = lenght; i; i >>= 1)
    if (1 == (i & 1)) bitcount++;
  if ((bitcount != 1 ) || (lenght < 16))
    {
      printf("%d lenght should be a power of 2 > 16 \n", lenght);
      exit(0);
    }
#ifdef IMAGE
  genImage(lenght,256);
#else
  genColorMap(lenght);
#endif
  return 0;
}
