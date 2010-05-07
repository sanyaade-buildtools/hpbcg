#include <stdio.h>
#include <stdlib.h>


int multiplyFunc(int i)
{
  return i*42;
}

int main(int argc, char * argv[])
{
  int i;
  if (argc < 2)
    {
      printf("%s [Multiply factor]\n", argv[0]);
      exit(0);
    }

  for (i = 1; i < 11; ++i) printf("%3d ", i);
  printf("\n");
  for (i = 1; i < 11; ++i) printf("%3d ", multiplyFunc(i));
  printf("\n");
  return 0;
}
