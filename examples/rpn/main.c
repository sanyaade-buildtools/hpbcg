#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <hpbcg-asm-common.h>

typedef int (*pifi)(int);
pifi rpnCompile(char *expr);

int __attribute__((noinline)) static_f2c(int i) 
{
  return (i-32)*5/9;
}

int __attribute__((noinline)) static_c2f(int i)
{
  return (i*9/5)+32;
}

int rpnEval(char *expr, int value)
{
  int Stack[10];
  int top = 0;
  Stack[top++] = value;
  while (*expr)
    {
      char buf[32];
      int n;
      if (sscanf(expr, "%[0-9]%n", buf, &n)) 
	{
	  expr += n - 1;
	  Stack[top++] = strtol(buf, 0, 0);
	 }
      else if (*expr == '+') 
	{ Stack[top-2] = Stack[top-2] + Stack[top-1]; top--; }
      else if (*expr == '-') 
	{ Stack[top-2] = Stack[top-2] - Stack[top-1]; top--; }
      else if (*expr == '*')
	{ Stack[top-2] = Stack[top-2] * Stack[top-1]; top--; }
      else if (*expr == '/')
	{ Stack[top-2] = Stack[top-2] / Stack[top-1]; top--; }
      else {
	fprintf(stderr, "cannot compile: %s\n", expr);
	abort();
      }
      ++expr;
    }
  if (1 != top)
    {
      fprintf(stderr, "incorrect stack pointer\n");
      abort();
    }
  return Stack[0];
} /* rpnEval */

int main(int argc, char * argv[])
{
  int i;
  if (argc == 1)
    {
      uint64_t startTick = getTick();
      pifi c2f = rpnCompile("9*5/32+");
      pifi f2c = rpnCompile("32-5*9/");
      printf("Code gen %llu ticks \n", getTick() - startTick);
      printf("\nC:");
      for (i = 0; i <= 100; i+= 10) printf("%3d ", i);
      printf("\nF:");
      for (i = 0; i <= 100; i+= 10) printf("%3d ", c2f(i));
      printf("\n");
      printf("\nF:");
      for (i = 32; i <= 212; i+= 10) printf("%3d ", i);
      printf("\nC:");
      for (i = 32; i <= 212; i+= 10) printf("%3d ", f2c(i));
      printf("\n");
      startTick = getTick();
      for (i = 0; i  <= 100; i+= 10)  	c2f(i);
      for (i = 32; i <= 212; i+= 10) 	f2c(i);
      printf("%llu ticks compiled\n", getTick() - startTick);
      startTick = getTick();
      for (i = 0; i  <= 100; i+= 10)  	rpnEval("9*5/32+", i);
      for (i = 32; i <= 212; i+= 10) 	rpnEval("32-5*9/", i);
      printf("%llu ticks interpreted\n", getTick() - startTick);
      startTick = getTick();
      for (i = 0; i  <= 100; i+= 10)  	static_c2f(i);
      for (i = 32; i <= 212; i+= 10) 	static_f2c(i);
      printf("%llu ticks static compiled\n", getTick() - startTick);
    }
  else
    {
      pifi fun = rpnCompile (argv[1]);
      printf("\nC:");
      for (i = 0; i <= 100; i+= 10) printf("%4d ", i);
      printf("\nF:");
      for (i = 0; i <= 100; i+= 10) printf("%4d ", fun(i));
      printf("\n");
    }
  return 0;
}
