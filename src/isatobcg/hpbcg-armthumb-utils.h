/*
 * hpbcg-arm-thumb-utils.h
 *
 */

#include <hpbcg-asm-common.h>
#include <sys/mman.h>
#include <unistd.h>

#define ADDINSN(VAL) (*(hpbcg_asm_pc++) = (VAL))
#define ORG(PTR) (hpbcg_asm_pc = (insn *) PTR)

typedef uint16_t insn;
static insn *hpbcg_asm_pc;
static void iflush(register insn *addr, register insn *last)
{
  long pageSize= getpagesize();
  void *ptmp= (char *)((long)addr & ~(pageSize - 1));
  if (mprotect(ptmp, (last - addr), PROT_READ | PROT_WRITE | PROT_EXEC))
    {
      perror("iflush: mprotect");
      exit(-1);
    }
#ifdef ASM_DEBUG
  printf("Flush data cache from %p to %p\n", addr, last);  
#endif
}

