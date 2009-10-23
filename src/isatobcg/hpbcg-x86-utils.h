/*
 * hpbcg-x86-utils.h
 *
 */

#include <hpbcg-asm-common.h>

#define ADDINSN(VAL) (*(hpbcg_asm_pc++) = (VAL))
#define ORG(PTR) (hpbcg_asm_pc = (insn *) PTR)

typedef unsigned int insn;
static insn *hpbcg_asm_pc;

static void iflush(register insn *addr, register insn *last)
{
  (void) printf("Flush data cache from %p to %p\n", addr, last);  
}

