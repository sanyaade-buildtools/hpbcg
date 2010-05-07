/*
 * cell-utils.h
 *
 */

#include <hpbcg-asm-common.h>


static void hpbcg_cell_addInsn(uint64_t insn);

#define ADDINSN(VAL) hpbcg_cell_addInsn(VAL)
#define THEADDINSN(VAL) (*(hpbcg_asm_pc++) = (VAL))
#define ORG(PTR) (hpbcg_asm_pc = (insn *) PTR)

typedef unsigned int insn;
static insn *hpbcg_asm_pc;
static int hpbcg_cell_doSchedule = 1; /* Do dual pipeline scheduling by default */
static void iflush(register insn *addr, register insn *last)
{
#ifdef ASM_DEBUG
  printf("Flush data cache from %p to %p\n", addr, last);  
  printf("(No-op)\n");  
#endif
}


/* 
 * General algo : 
 * if (1 == hpbcg_asm_pc % 2) && (0 == slot_bit) AddInsn (NOP_L, hpbcg_asm_pc++)
 * if (0 == hpbcg_asm_pc % 2) && (1 == slot_bit) AddInsn (NOP_X, hpbcg_asm_pc++)
 * AddInsn (VAL , hpbcg_asm_pc++)
 */
static void hpbcg_cell_addInsn(uint64_t insn)
{
  int mask;

#if 1
  if (hpbcg_cell_doSchedule)
    {
      mask = (insn >> 32) & 0x1;
#if 0
      printf("mask %d asm_pc mod 8 %d\n", mask, ((uint32_t) hpbcg_asm_pc) % 8);
#endif
      if ((0 == (uint32_t) hpbcg_asm_pc % 8) && (1 == mask)) 
	{
	  THEADDINSN (0x40200000); 
#ifdef ASM_DEBUG
	  printf("-> : nop (execute)\n");
#endif
	} else if ((4 == ((uint32_t) hpbcg_asm_pc) % 8) && (0 == mask)) 
	{
	  THEADDINSN (0x00200000); 
#ifdef ASM_DEBUG
	  printf("-> : lnop \n");
#endif
	}
    }
  THEADDINSN (insn);
#else
  /* mask Cell Slot | hpbcg_asm_pc parity */
  mask = ((insn >> 31) & 0x2) | (((uint64_t) hpbcg_asm_pc >> 3) & 0x2);
  theinsn = insn & 0xffffffff;
  switch (mask)
    {
    case 0: 
    case 3: break; 		/* Correct slot / address nothing to do */
    case 1: THEADDINSN (0x00200000); 
#ifdef ASM_DEBUG
      printf("-> : nop (load)\n");
#endif
      break; /* Nop Load */
    case 2: THEADDINSN (0x40200000); 
#ifdef ASM_DEBUG
      printf("-> : nop (execute)\n");
#endif
      break; /* Nop Execute */
    default:
      (void) printf("cell_addInsn mask :%d should not happen\n", mask);
      exit(-1);
      break;
    }
  THEADDINSN (theinsn);
#endif
} /* cell_addInsn */
