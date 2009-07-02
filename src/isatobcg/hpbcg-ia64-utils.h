/*
 * ia64-utils.h
 *
 */

#include <hpbcg-asm-common.h>
#include <assert.h>

static int ia64_addInsn(ui64_t insn, char stop);

#define ADDINSN(VAL, STOP) ia64_addInsn((ui64_t) (VAL), STOP)
#define ORG(PTR) 	(hpbcg_asm_pc = (insn *) PTR)
#define PROC(PTR, DATA) ({ bundle b = {(ui64_t) PTR, (ui64_t) DATA}; _GEN(b); hpbcg_asm_pc++;})
#define _GENL(B)	(*((long *)hpbcg_asm_pc)= (long)(B))
#define _GEN(B)		(*hpbcg_asm_pc = (B))
#define _BBUNDLE(TMPL, S0, S1, S2) ({ bundle b = {(S1) <<46 | (S0) << 5 | TMPL, (S2) << 23 | (S1) >>18 }; _GEN(b); hpbcg_asm_pc++;})

enum ia64_Type
{
  ia64_TypeNil= 0,
  ia64_TypeA,			/* 001 */
  ia64_TypeI,			/* 010 */
  ia64_TypeM,			/* 011 */
  ia64_TypeB,			/* 100 */
  ia64_TypeF,			/* 101 */
  ia64_TypeX,			/* 110 */
  ia64_NumTypes
};

enum ia64_Unit
{
  ia64_UnitNil= 0,
  ia64_UnitI,
  ia64_UnitM,
  ia64_UnitB,
  ia64_UnitF,
  ia64_UnitL,
  ia64_UnitX,
  ia64_NumUnits
};

#define NOPI   0x8000000ULL
#define NOPM   NOPI
#define NOPB   0x4000000000ULL
#define NOPF   NOPI
/* Template number depending on the instruction type */
/* Contributed by Ali Guellal <guellal.ali@gmail.com> during
 * Master stage
*/
static const char ia64_tmpl[14][14][14] =
  {
      /*         0   a   i   m   b   f  x   0    A   I   M   B   F   X */
    /* 00. */ {{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 00. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 00. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 00. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 00. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 00. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 00. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 00. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 00. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 00. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 00. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 00. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 00. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 00. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},    },
      /*         0   a   i   m   b   f   x   0   A   I   M   B   F   X */
    /* 00. */ {{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* aa. */  {-1,  0,  8, -1, 16, 14,  4, -1,  1,  9, -1, -1, 17,  5},
    /* ai. */  {-1,  0,  0, -1, 16, -1,  4, -1,  1,  1, -1, 17, -1,  5},
    /* am. */  {-1,  8,  8, -1, 24, 14, -1, -1,  9,  9, -1, 25, 15, -1},
    /* ab. */  {-1, -1, -1, -1, 18, -1, -1, -1, -1, -1, -1, 19, -1, -1},
    /* af. */  {-1, -1, 12, -1, 28, -1, -1, -1, -1, 13, -1, 29, -1, -1},
    /* ax. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 00. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* aA. */  {-1,  2,  2, -1, -1, -1, -1, -1,  3,  3, -1, -1, -1, -1},
    /* aI. */  {-1,  2,  2, -1, -1, -1, -1, -1,  3,  3, -1, -1, -1, -1},
    /* aM. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* aB. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* aF. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* aX. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},    },
      /*         0   a   i   m   b   f  x    0   A   I   M   B   F   X */
    /* 00. */ {{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* ia. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* ii. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* im. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* ib. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* if. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* ix. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},   
    /* 00. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* iA. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* iI. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* iM. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* iB. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* iF. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* iX. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},   },
      /*         0   a   i   m   b   f   x   0   A   I   M   B   F   X */
    /* 00. */ {{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* ma. */  {-1,  0,  0, -1, 16, 14, -1, -1,  1,  1, -1, 17, 15, -1},
    /* mi. */  {-1,  0,  0, -1, 16, -1, -1, -1,  1,  1, -1, 17, -1, -1},
    /* mm. */  {-1,  8,  8, -1, 24, 14, -1, -1,  9,  9, -1, 25, 15, -1},
    /* mb. */  {-1, -1, -1, -1, 18, -1, -1, -1, -1, -1, -1, 19, -1, -1},
    /* mf. */  {-1, 12, 12, -1, -1, -1, -1, -1, 13, 13, -1, -1, -1, -1},
    /* mx. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 00. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* mA. */  {-1,  2,  2, -1, -1, -1, -1, -1,  3,  3, -1, -1, -1, -1},
    /* mI. */  {-1,  2,  2, -1, -1, -1, -1, -1,  3,  3, -1, -1, -1, -1},
    /* mM. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* mB. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* mF. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* mX. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},   },
      /*         0   a   i   m   b   f  x    0   A   I   M   B   F   X */
    /* 00. */ {{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* ba. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* bi. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* bm. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* bb. */  {-1, -1, -1, -1, 22, -1, -1, -1, -1, -1, -1, 23, -1, -1},
    /* bf. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* bx. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 00. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* bA. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* bI. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* bM. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* bB. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* bF. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* bX. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},   },
      /*         0   a   i   m   b   f  x    0   A   I   M   B   F   X */
    /* 00. */ {{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* fa. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* fi. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* fm. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* fb. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* ff. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* fx. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 00. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* fA. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* fI. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* fM. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* fB. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* fF. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* fX. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},   },
      /*         0   a   i   m   b   f  x    0   A   I   M   B   F   X */
    /* 00. */ {{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* xa. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* xi. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* xm. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* xb. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* xf. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* xx. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 00. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* xA. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* xI. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* xM. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* xB. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* xF. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* xX. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},   },
      /*         0   a   i   m   b   f  x    0   A   I   M   B   F   X */
    /* 00. */ {{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 0a. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 0i. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 0m. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 0b. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 0f. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 0x. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 00. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 0A. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 0I. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 0M. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 0B. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 0F. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 0X. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},   },
      /*         0   a   i   m   b   f  x    0   A   I   M   B   F   X */
    /* 00. */ {{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Aa. */  {-1, 10, 10, -1, -1, -1, -1, -1, 11, 11, -1, -1, -1, -1},
    /* Ai. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Am. */  {-1, 10, 10, -1, -1, -1, -1, -1, 11, 11, -1, -1, -1, -1},
    /* Ab. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Af. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Ax. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 00. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* AA. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* AI. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* AM. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* AB. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* AF. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* AX. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},   },
      /*         0   a   i   m   b   f  x    0   A   I   M   B   F   X */
    /* 00. */ {{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Ia. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Ii. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Im. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Ib. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* If. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Ix. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 00. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Ia. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Ii. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Im. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Ib. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* If. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Ix. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},   },
      /*         0   a   i   m   b   f  x    0   A   I   M   B   F   X */
    /* 00. */ {{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Ma. */  {-1, 10, 10, -1, -1, -1, -1, -1, 11, 11, -1, -1, -1, -1},
    /* Mi. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Mm. */  {-1, 10, 10, -1, -1, -1, -1, -1, 11, 11, -1, -1, -1, -1},
    /* Mb. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Mf. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Mx. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 00. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* MA. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* MI. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* MM. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* MB. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* MF. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* MX. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},   },
      /*         0   a   i   m   b   f  x    0   A   I   M   B   F   X */
    /* 00. */ {{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Ba. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Bi. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Bm. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Bb. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Bf. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* BB. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 00. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* BA. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* BI. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* BM. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* BB. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* BF. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* BX. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},   },
      /*         0   a   i   m   b   f  x    0   A   I   M   B   F   X */
    /* 00. */ {{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Fa. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Fi. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Fm. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Fb. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Ff. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Fx. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 00. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* FA. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* FI. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* FM. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* FB. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* FF. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* FX. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},   },
      /*         0   a   i   m   b   f  x    0   A   I   M   B   F   X */
    /* 00. */ {{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Xa. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Xi. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Xm. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Xb. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Xf. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* Xx. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 00. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* XA. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* XI. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* XM. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* XB. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* XF. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* XX. */  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},   },
  };
 
struct ia64_Template
{
  const char	    *name;
  enum ia64_Unit  unit[3];

};

static const struct ia64_Template ia64_template[32]=
{
  /* 00 */  { "mii", { ia64_UnitM, ia64_UnitI, ia64_UnitI } },
  /* 01 */  { "miI", { ia64_UnitM, ia64_UnitI, ia64_UnitI } },
  /* 02 */  { "mIi", { ia64_UnitM, ia64_UnitI, ia64_UnitI } },
  /* 03 */  { "mII", { ia64_UnitM, ia64_UnitI, ia64_UnitI } },
  /* 04 */  { "mlx", { ia64_UnitM, ia64_UnitL, ia64_UnitX } },
  /* 05 */  { "mlX", { ia64_UnitM, ia64_UnitL, ia64_UnitX } },
  /* 06 */  { 0,     { 0, 0, 0 } },
  /* 07 */  { 0,     { 0, 0, 0 } },
  /* 08 */  { "mmi", { ia64_UnitM, ia64_UnitM, ia64_UnitI } },
  /* 09 */  { "mmI", { ia64_UnitM, ia64_UnitM, ia64_UnitI } },
  /* 0a */  { "mMi", { ia64_UnitM, ia64_UnitM, ia64_UnitI } },
  /* 0b */  { "mMI", { ia64_UnitM, ia64_UnitM, ia64_UnitI } },
  /* 0c */  { "mfi", { ia64_UnitM, ia64_UnitF, ia64_UnitI } },
  /* 0d */  { "mfI", { ia64_UnitM, ia64_UnitF, ia64_UnitI } },
  /* 0e */  { "mmf", { ia64_UnitM, ia64_UnitM, ia64_UnitF } },
  /* 0f */  { "mmF", { ia64_UnitM, ia64_UnitM, ia64_UnitF } },
  /* 10 */  { "mib", { ia64_UnitM, ia64_UnitI, ia64_UnitB } },
  /* 11 */  { "miB", { ia64_UnitM, ia64_UnitI, ia64_UnitB } },
  /* 12 */  { "mbb", { ia64_UnitM, ia64_UnitB, ia64_UnitB } },
  /* 13 */  { "mbB", { ia64_UnitM, ia64_UnitB, ia64_UnitB } },
  /* 14 */  { 0,     { 0, 0, 0 } },
  /* 15 */  { 0,     { 0, 0, 0 } },
  /* 16 */  { "bbb", { ia64_UnitB, ia64_UnitB, ia64_UnitB } },
  /* 17 */  { "bbB", { ia64_UnitB, ia64_UnitB, ia64_UnitB } },
  /* 18 */  { "mmb", { ia64_UnitM, ia64_UnitM, ia64_UnitB } },
  /* 19 */  { "mmB", { ia64_UnitM, ia64_UnitM, ia64_UnitB } },
  /* 1a */  { 0,     { 0, 0, 0 } },
  /* 1b */  { 0,     { 0, 0, 0 } },
  /* 1c */  { "mfb", { ia64_UnitM, ia64_UnitF, ia64_UnitB } },
  /* 1d */  { "mfB", { ia64_UnitM, ia64_UnitF, ia64_UnitB } },
  /* 1e */  { 0,     { 0, 0, 0 } },
  /* 1f */  { 0,     { 0, 0, 0 } },
};

typedef struct {
  ui64_t lo;
  ui64_t hi;
} bundle;
typedef bundle insn;
static insn *hpbcg_asm_pc;

typedef struct 
{
  char ia64_insnType;
  ui64_t ia64_insn;
  char ia64_stop;
} ia64_insns;
#define INSNMAX 3
static ia64_insns ia64_slots[INSNMAX];
static int ia64_slotCount = 0;


void isAsserted()
{
#if ASM_DEBUG
  printf("sizeof ui64_t %d bits\n", (int) (8*sizeof (ui64_t)));
  printf("sizeof ui32_t %d bits\n", (int) (8*sizeof (ui32_t)));
  printf("sizeof insn   %d bits\n", (int) (8*sizeof (insn)));
#endif
  assert(8 == sizeof (ui64_t));
  assert(4 == sizeof (ui32_t));
  hasBeenAsserted = 1;
} /* isAsserted */

char insnTypeArray[] = "_aimbfx_AIMBFX";
char insnType(char type, int stop)
{
  int i = type+stop*7;
  assert(i < sizeof(insnTypeArray));
  return insnTypeArray[i];
} /* insnType */

#ifdef ASM_DEBUG
static void pInsn(ui64_t insn, char type, char stop)
{
  printf("%c: 0x%0llx\n", insnType(type, stop), insn);
}
#endif

static int ia64_emitInsn()
{
  char tmplate[4];
  char tmplval, stop;
  int i, s0, s1, s2;

  for (i = 0; i < 3; ++i)
    {
      tmplate[i] = insnType(ia64_slots[i].ia64_insnType, ia64_slots[i].ia64_stop);
    }
  tmplate[i] = '\0';
  s0 = (int) ia64_slots[0].ia64_insnType + (ia64_slots[0].ia64_stop?7:0);
  s1 = (int) ia64_slots[1].ia64_insnType + (ia64_slots[1].ia64_stop?7:0);
  s2 = (int) ia64_slots[2].ia64_insnType + (ia64_slots[2].ia64_stop?7:0);
  tmplval = ia64_tmpl[s0][s1][s2];
  if (-1 != tmplval)		/* Found template statically */
   {
#ifdef ASM_DEBUG
     printf("S: %s %d\n", tmplate, tmplval);
#endif
     _BBUNDLE(tmplval, ia64_slots[0].ia64_insn, ia64_slots[1].ia64_insn, ia64_slots[2].ia64_insn);
      ia64_slotCount = 0;
   }
  else
    {				/* Emit the 1st insn, then reschedule */
      ia64_insns myInsn = ia64_slots[0];
      stop = myInsn.ia64_stop;
      switch (myInsn.ia64_insnType)
	{
	case ia64_TypeI: 
#ifdef ASM_DEBUG
	  printf("D_I: %s\n", (stop)?"mIi":"mii");
#endif
	  if (stop) {_BBUNDLE(0x01, NOPM, NOPI, myInsn.ia64_insn); }
	  else	    {_BBUNDLE(0x00, NOPM, NOPI, myInsn.ia64_insn); }
	  break;
	case ia64_TypeA: 
#ifdef ASM_DEBUG
	  printf("D_A: %s\n", (stop)?"mIi":"mii");
#endif
	  if (stop) { _BBUNDLE(0x01, NOPM, myInsn.ia64_insn, NOPI); }
	  else	    { _BBUNDLE(0x00, NOPM, myInsn.ia64_insn, NOPI); }
	  break;
	case ia64_TypeM: 
#ifdef ASM_DEBUG
	  printf("D_M: %s\n", (stop)?"mIi":"mii");
#endif
	  if (stop) { _BBUNDLE(0x01, myInsn.ia64_insn, NOPI, NOPI); }
	  else	    { _BBUNDLE(0x00, myInsn.ia64_insn, NOPI, NOPI); }
	  break;
	case ia64_TypeB: 
#ifdef ASM_DEBUG
	  printf("D_B: %s\n", (stop)?"bbB":"bbb"); 
#endif
	  if (stop) { _BBUNDLE(0x17, myInsn.ia64_insn, NOPB, NOPB); }
	  else	    { _BBUNDLE(0x16, myInsn.ia64_insn, NOPB, NOPB); }
	  break;
	case ia64_TypeF: 
#ifdef ASM_DEBUG
	  printf("D_F: %s\n", (stop)?"mfI":"mfi"); 
#endif
	  if (stop) { _BBUNDLE(0x0d, NOPM, myInsn.ia64_insn, NOPI); }
	  else	    { _BBUNDLE(0x0c, NOPM, myInsn.ia64_insn, NOPI); }
	  break;
	case ia64_TypeX: 
#ifdef ASM_DEBUG
	  printf("D_X: %s\n", (stop)?"mlX":"mlx"); 
#endif
	  printf("mlx not yet implemented\n");
	  exit(0);
	  break;
	default: 
	  printf("This case shoud not append s0 = %d\n", s0); exit(0); break;
	}
      ia64_slots[0] =  ia64_slots[1]; /* Replanify the following insns */
      ia64_slots[1] =  ia64_slots[2];
      ia64_slotCount--;
    }
#ifdef ASM_DEBUG
     printf("hpbcg_asm_pc = %p\n", hpbcg_asm_pc);
#endif
 return 0;
}


static int ia64_addInsn(ui64_t insn, char stop)
{
  char insnType =  (insn >> 41) & 0x7;
  ui64_t insnBin = insn & _MASK(41);

#ifdef NOTDEFINED
  pInsn(insnBin, insnType, stop);
#endif /* ASM_DEBUG */
  if (!hasBeenAsserted) isAsserted ();
  if (ia64_slotCount >= INSNMAX)
    {
      ia64_emitInsn();
    }
  ia64_slots[ia64_slotCount].ia64_insnType = insnType;
  ia64_slots[ia64_slotCount].ia64_insn = insnBin;
  ia64_slots[ia64_slotCount].ia64_stop = stop;
  ia64_slotCount++;
  return 0;
}

#include <hpbcg-ia64-cache.h>

