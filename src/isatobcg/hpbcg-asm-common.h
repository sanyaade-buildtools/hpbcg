/* 
 * asm-common.h
 * 
 * macro definitions common for all architectures
 * 
 */

#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long ui64_t;
typedef unsigned int ui32_t;


#define ASM_1_BEGIN
#define ASM_1_END
#define ASM_2_BEGIN
#define ASM_2_END


#define _UL(X)		((ui64_t)(X))
#define _MASK(N)	((ui64_t)((1ULL << (N))) -1)
#define LENOK(VAL, LEN) ((VAL) < (1ULL << (LEN+1))	\
	 ?((ui64_t) (VAL))					\
	 :ASMFAIL("unsigned long "#VAL" too large for "#LEN"-bit field line "))
#define ASMFAIL(MSG) asmFail(MSG, __FILE__, __LINE__,(char *) __func__)

int hasBeenAsserted = 0;
static int asmFail(char *msg, char *file, int line, char *function)
{
  fprintf(stderr, "%s: In function `%s':\n", file, function);
  fprintf(stderr, "%s:%d: %s\n", file, line, msg);
  abort();
  return 0;
}
