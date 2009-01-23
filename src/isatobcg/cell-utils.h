/*
 * cell-utils.h
 *
 */

#include <asm-common.h>

#define ADDINSN(VAL) (*(asm_pc++) = (VAL))
#define ORG(PTR) (asm_pc = (insn *) PTR)

typedef unsigned int insn;
static insn *asm_pc;

static void iflush(register insn *addr, register insn *last)
{
  
  register insn *dptr= addr;
  (void) printf("Flush !\n");
  while (dptr < last) {
    asm volatile ("dcbst 0,%0": :"r"(dptr));
    ++dptr;
  }
  asm volatile ("sync");
  while (addr < last) {
    asm volatile ("icbi 0,%0": :"r"(addr));
    ++addr;
  }
  asm volatile ("sync;isync");  
}
