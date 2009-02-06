/*
 * power4-utils.h
 *
 */

#include <asm-common.h>

#define ADDINSN(VAL) (*(asm_pc++) = (VAL))
#define ORG(PTR) (asm_pc = (insn *) PTR)

typedef unsigned int insn;
static insn *asm_pc;

static void iflush(register insn *addr, register insn *last)
{
  (void) printf("Flush data cache from %p to %p\n", addr, last);  
}
