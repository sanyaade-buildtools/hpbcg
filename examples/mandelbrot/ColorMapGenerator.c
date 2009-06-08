#include <stdio.h>
#include <stdlib.h>


void pColor(int r, int v, int b)
{
  printf("{%d, %d, %d},\n", r, v, b);
} /* pColor */

int main(int argc, char * argv[])
{
  int i, lenght, tmp;

  if (argc < 2)
    {
      printf("%s Lenght\n", argv[0]);
      exit(0);
    }
  lenght = atoi(argv[1]);
  printf("#define COLORMAPSIZE %d\n", lenght);
  printf("typedef struct {int r, v, b;}tColor;\n");
  printf("tColor thePalette[]=\n");
  printf("{\n");
  for (i = 0; i < lenght/2; ++i) { tmp = 2*i*255/lenght;          pColor(255, tmp, tmp); }
  for (i = 0; i < lenght/2; ++i) { tmp = (lenght-2*i)*255/lenght; pColor(255, tmp, tmp); }
  printf("};\n");
  return 0;
}
