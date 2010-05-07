#include <stdio.h>  /* -*- c -*- */
#include <stdlib.h>
#include <assert.h>
#include <hpbcg-asm-common.h>

typedef int (*pifi)(int);
pifi multiplyCompile(char *expr);

int main(int argc, char *argv[])
{
  int i;
  pifi multiplyFunc; 
  uint64_t startTick;
  if (argc < 2)
    {
      printf("%s [Multiply factor]\n", argv[0]);
      exit(0);
    }
  startTick = getTick();
  multiplyFunc = multiplyCompile(atoi(argv[1])); /* Generate code */
  printf("Code gen %d ticks \n", (int) (getTick() - startTick));
  for (i = 1; i < 11; ++i) printf("%3d ", i);
  printf("\n");
    for (i = 1; i < 11; ++i) printf("%3d ", multiplyFunc(i));
  printf("\n");
  return 0;
}
