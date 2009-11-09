#include <stdio.h>
#include <stdlib.h>

typedef int (*pifi)(int);
pifi rpnCompile(char *expr);

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
      pifi c2f= rpnCompile("9*5/32+");
      pifi f2c= rpnCompile("32-5*9/");
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
