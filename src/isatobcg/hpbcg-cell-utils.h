/*
 * cell-utils.h
 *
 */

#include <hpbcg-asm-common.h>


static void cell_addInsn(ui64_t insn);

#define ADDINSN(VAL) cell_addInsn(VAL)
#define THEADDINSN(VAL) (*(asm_pc++) = (VAL))
#define ORG(PTR) (asm_pc = (insn *) PTR)

typedef unsigned int insn;
static insn *asm_pc;

static void iflush(register insn *addr, register insn *last)
{
  (void) printf("Flush data cache from %p to %p\n", addr, last);  
}


/* 
 * General algo : 
 * if (1 == asm_pc % 2) && (0 == slot_bit) AddInsn (NOP_L, asm_pc++)
 * if (0 == asm_pc % 2) && (1 == slot_bit) AddInsn (NOP_X, asm_pc++)
 * AddInsn (VAL , asm_pc++)
 */
static void cell_addInsn(ui64_t insn)
{
  int mask;
  ui32_t theinsn;

  /* mask Cell Slot | asm_pc parity */
  mask = ((insn >> 31) & 0x2) | ((ui64_t) asm_pc %  2);
  theinsn = insn & 0xffffffff;
  switch (mask)
    {
    case 0: 
    case 3: break;
    case 1: THEADDINSN (0x00200000); break; /* Nop Load */
    case 2: THEADDINSN (0x40200000); break; /* Nop Execute */
    default:
      (void) printf("cell_addInsn mask :%d should not happen\n", mask);
      exit(-1);
      break;
    }
  THEADDINSN (theinsn);
} /* cell_addInsn */
