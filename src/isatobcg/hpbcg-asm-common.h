/* 
 * asm-common.h
 * 
 * macro definitions common for all architectures
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

typedef unsigned long long ui64_t;
typedef unsigned int ui32_t;


#define ASM_1_BEGIN
#define ASM_1_END
#define ASM_2_BEGIN
#define ASM_2_END


#define _UL(X)		((ui64_t)(X))
#define _MASK(N)	((ui64_t)((1ULL << (N))) -1)
#define LENOK(VAL, LEN) ((VAL) < (1ULL << (LEN))?(ui64_t)(VAL)		\
	 :ASMFAIL("unsigned long "#VAL" too large for "#LEN"-bit field line "))
#define ASMFAIL(MSG) asmFail(MSG, __FILE__, __LINE__,(char *) __func__)
#define LABEL(IDLABEL) (IDLABEL = hpbcg_asm_pc)

int hasBeenAsserted = 0;
static int asmFail(char *msg, char *file, int line, char *function)
{
  fprintf(stderr, "%s: In function `%s':\n", file, function);
  fprintf(stderr, "%s:%d: %s\n", file, line, msg);
  abort();
  return 0;
}

/* Return a string which help to identify the architecture */
char * getArchName()
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

