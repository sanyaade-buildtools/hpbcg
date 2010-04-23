/* 
 * asm-common.h
 * 
 * macro definitions common for all architectures
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>


#define ASM_1_BEGIN {
#define ASM_1_END   }
#define ASM_2_BEGIN
#define ASM_2_END


#define _UL(X)		((uint64_t)(X))
#define _MASK(N)	((uint64_t)((1ULL << (N))) -1)
#define LENOK(VAL, LEN) ((VAL) < (1ULL << (LEN))?(uint64_t)(VAL)		\
	 :ASMFAIL("unsigned long "#VAL" too large for "#LEN"-bit field line "))
#define ASMFAIL(MSG) asmFail(MSG, __FILE__, __LINE__,(char *) __func__)
#define LABEL(IDLABEL) (IDLABEL = hpbcg_asm_pc)

static int hasBeenAsserted = 0;
static int asmFail(char *msg, char *file, int line, char *function)
{
  fprintf(stderr, "%s: In function `%s':\n", file, function);
  fprintf(stderr, "%s:%d: %s\n", file, line, msg);
  abort();
  return 0;
}

/* Return a string which help to identify the architecture */
static char * getArchName()
{
  char * msg;

  msg = malloc(1024);
/* How to know which flag are defined : gcc -dM -E - < /dev/null | sort */
#if 0
 babel:/bgsys/drivers/V1R2M0_200_2008-080513P/ppc/arch/include
    _bgp_ProcessorVersion()
    _bgp_mfspr(RegId)
#endif
#if defined(__i386__)
  sprintf(msg, "%s", "i386:");
#else
#if defined(__powerpc__) || defined(_POWER)
  int procId;
  char *name;
  asm("mfspr %0, 287" : "=r" (procId));
  switch ((procId >> 16) & 0xFFFF)
    {
    case 0x0033: name = "POWER_NORTHSTAR"; 	break;
    case 0x0034: name = "POWER_PULSAR";		break;
    case 0x0035: name = "POWER_POWER4"; 	break;
    case 0x0036: name = "POWER_ICESTAR"; 	break;
    case 0x0037: name = "POWER_SSTAR"; 		break;
    case 0x0038: name = "POWER_POWER4p"; 	break;
    case 0x0039: name = "POWER_970"; 		break;
    case 0x003A: name = "POWER_POWER5"; 	break;
    case 0x003B: name = "POWER_POWER5p"; 	break;
    case 0x003C: name = "POWER_970FX"; 		break;
    case 0x003E: name = "POWER_POWER6"; 	break;
    case 0x0040: name = "POWER_630";	 	break;
    case 0x0041: name = "POWER_630p";     	break;
    case 0x0044: name = "POWER_970MP"; 		break;
    case 0x0045: name = "POWER_970GX"; 		break;
    case 0x0070: name = "POWER_CELL";		break;
    default:     name = "POWER_UNKOWN"; 	break;
    }
  sprintf(msg, "%s: %s revision 0x%X", "power", name, procId & 0xFFFF);
 #else
#if defined(__SPU__)
  sprintf(msg, "%s", "CELL:");
 #else
  sprintf(msg, "%s", "Unknown arch");
 #endif
 #endif
#endif
  return msg;
}

#if defined(__i386__) || defined(__x86_64__)
/* http://fr.wikipedia.org/wiki/RDTSC */
#define getTickDefined 1
static uint64_t getTick() {
  uint64_t x;
  __asm__ volatile ("rdtsc" : "=A" (x));
  return x;
}
#endif 				/* i386 */

#if defined(__ia64__)
#include <stdint.h>
/* http://www.fftw.org/cycle.h */
#define getTickDefined 1
#ifdef __ECC
static uint64_t __getReg (int whichReg);
#pragma intrinsic(__getReg);
#define INL_REGID_APITC 3116 
#endif       

static uint64_t getTick()
{
#ifdef __ECC
  return __getReg (INL_REGID_APITC);
#else
  long result;
  __asm__ __volatile__("mov %0=ar.itc" : "=r"(result) :: "memory");
  while (__builtin_expect ((int) result == -1, 0))
    __asm__ __volatile__("mov %0=ar.itc" : "=r"(result) ::"memory");
  return result;
#endif
} 
#endif	/* __ia64__ */

#if defined(__SPU__)
#define getTickDefined 1
#include <stdint.h>
static hpbcg_decrementerisInitialized = 0;
static uint64_t getTick()
{
  if (!hpbcg_decrementerisInitialized)
    {
      spu_write_decrementer(0xFFFFFFFF);
      hpbcg_decrementerisInitialized  = 1;
    }
  return spu_read_decrementer()
}	/* getTick() */
#endif	/* __SPU__ */


#if defined(__PPC__)
#define getTickDefined 1
#include <stdint.h>
static uint64_t getTick()
{
     unsigned int tbl, tbu0, tbu1;
     uint64_t high, low;
     do {
	  __asm__ __volatile__ ("mftbu %0" : "=r"(tbu0));
	  __asm__ __volatile__ ("mftb %0"  : "=r"(tbl));
	  __asm__ __volatile__ ("mftbu %0" : "=r"(tbu1));
     } while (tbu0 != tbu1);
     high = tbu1;
     low = tbl;
     return (high << 32) | low;
}
#endif	/* __PPC__ */

#if defined(__arm__)
#define getTickDefined 1
#include <stdint.h>
#include <sys/time.h>
static uint64_t getTick()
{
  int res;
  struct timeval MyTime;
  uint64_t tick;
  res = gettimeofday(&MyTime, NULL);
  tick = MyTime.tv_sec * 1000000 + MyTime.tv_usec;
  if (0 == res)  return tick;
  else return 0;
}
#endif	/* __arm__ */

#if !defined(getTickDefined)
#warning "getTick not defined"
#endif
