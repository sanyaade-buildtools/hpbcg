#include <strings.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/mman.h>



#define SIZE 100

extern int MyAdd (int i);

typedef int (*pifi)(int);

#ifdef __arm__
#define ARCHITECTURE "armthumb"
unsigned char MyArray[]=  { 0x1f, 0x30, 
			    0x70, 0x47 };
#endif
#ifdef __i386__
#define ARCHITECTURE "x86"
unsigned char MyArray[]=  {
  0x55, 		/* push   %ebp */
  0x89, 0xe5,           /* mov    %esp,%ebp */
  0x8b, 0x45, 0x08,     /* mov    0x8(%ebp),%eax */
  0x5d,                 /* pop    %ebp */
  0x83, 0xc0, 0x1f,     /* add    $0x1f,%eax */
  0xc3                  /* ret     */
 };
#endif

void iflush(char *addr, char *last)
{
  long pageSize= getpagesize();
  long size = last - addr;
  void *ptmp= (char *)((long)addr & ~(pageSize - 1));
  
#if 1
  printf("iflush:  page size %d frontiere %p\n", pageSize, ptmp);
#endif
  if (mprotect(ptmp, size, PROT_READ | PROT_WRITE | PROT_EXEC))
    {
      perror("iflush: mprotect");
      return;
    }
}

pifi multiplyFunc;
int main()
{
  int res;

#ifdef __arm__
  multiplyFunc = (pifi) MyArray+1;
#else
  multiplyFunc = (pifi) MyArray;
#endif  
  iflush (MyArray, MyArray + sizeof (MyArray));
  printf ("Architecture %s Function pointer %p\n", ARCHITECTURE, multiplyFunc);
  res = MyAdd (11);
  printf ("Static  result %d\n", res);
  res = multiplyFunc (11);
  printf ("Dynamic result %d\n", res);
  return 0;
}


