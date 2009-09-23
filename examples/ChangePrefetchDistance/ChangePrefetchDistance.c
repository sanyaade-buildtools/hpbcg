#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static const char* ia64_template[32]=
{
  /* 00 */  "mii",
  /* 01 */  "miI",
  /* 02 */  "mIi",
  /* 03 */  "mII",
  /* 04 */  "mlx",
  /* 05 */  "mlX",
  /* 06 */  "UKN",
  /* 07 */  "UKN",
  /* 08 */  "mmi",
  /* 09 */  "mmI",
  /* 0a */  "mMi",
  /* 0b */  "mMI",
  /* 0c */  "mfi",
  /* 0d */  "mfI",
  /* 0e */  "mmf",
  /* 0f */  "mmF",
  /* 10 */  "mib",
  /* 11 */  "miB",
  /* 12 */  "mbb",
  /* 13 */  "mbB",
  /* 14 */  "UKN" ,
  /* 15 */  "UKN" ,
  /* 16 */  "bbb",
  /* 17 */  "bbB",
  /* 18 */  "mmb",
  /* 19 */  "mmB",
  /* 1a */  "UKN" ,
  /* 1b */  "UKN" ,
  /* 1c */  "mfb",
  /* 1d */  "mfB",
  /* 1e */  "UKN" ,
  /* 1f */  "UKN" ,
};
typedef struct {
  int64_t lo;
  int64_t hi;
} bundle;
typedef bundle insn_t;

#define DEBUG 0

char arrayFunction[][16] __attribute__ ((aligned (16)))=
{
#include "copyItaniumIcc.h"
} ;
#if 0
       1         1         1
       2         1         0         9         8         7         6         5         4         3         2         1         
76543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210
X           slot 2                      XX         slot 1                        XX         slot 0                        XX   X
X                          hi                                  XX                            lo                                X
#endif

void toBin(int64_t val, int size)
{
  if (size > 0) toBin(val >> 1, size-1);
  printf("%c", (val & 0x1)?'1':'0');
  if (64 == size) printf("\n");
} /* toBin */



int64_t toInsn0(insn_t * insnAddress)
{
 insn_t theBundle;
 int64_t insn0;

 theBundle = * insnAddress;
 insn0 = (theBundle.lo >> 5) & 0x1FFFFFFFFFFLL; /* 41 bits i0 */
 return insn0;
}

int64_t toInsn1(insn_t * insnAddress)
{
 insn_t theBundle;
 int64_t tmp1, tmp2;

 theBundle = * insnAddress;
 tmp1  = (theBundle.hi & 0x7FFFFFFLL);   /* 23 bits in hi */
 tmp2 = (theBundle.lo >> 46 ) & 0x3FFFF; /* 18 bits in hi */
 return ((tmp1 << 18) | tmp2);
}

int64_t toInsn2(insn_t * insnAddress)
{
 insn_t theBundle;
 int64_t insn2;

 theBundle = * insnAddress;
 insn2 = (theBundle.hi >> 24) & 0x1FFFFFFFFFFLL; /* 41 bits i2 */
 return insn2;
}

int toTemplate(insn_t * insnAddress)
{
  insn_t theBundle;
  int template;

  theBundle = * insnAddress;
  template = theBundle.lo & 0x1F; /* 5 bit template */
  return template;
}
void ChangePrefetchDistance (insn_t * insnAddress, int slotNumber, int PrefetchDistance)
{

} /* ChangePrefetchDistance */

int WhichBundleM14(insn_t * insnAddress, int majorOpcode, int minorOpcode)
{
  int insnMajorOpcode, insnMinorOpcode;
  int64_t insn;

  insn = toInsn0(insnAddress);
  insnMajorOpcode = (insn >> 37) & 0xF;
  insnMinorOpcode = (insn >> 30) & 0x3F;
  if ((insnMajorOpcode == majorOpcode) && (insnMinorOpcode == minorOpcode)) return 0;

  insn = toInsn1(insnAddress);
  insnMajorOpcode = (insn >> 37) & 0xF;
  insnMinorOpcode = (insn >> 30) & 0x3F;
  if ((insnMajorOpcode == majorOpcode) && (insnMinorOpcode == minorOpcode)) return 1;

  insn = toInsn2(insnAddress);
  insnMajorOpcode = (insn >> 37) & 0xF;
  insnMinorOpcode = (insn >> 30) & 0x3F;
  if ((insnMajorOpcode == majorOpcode) && (insnMinorOpcode == minorOpcode)) return 2;
  return -1;
}

int WhichBundleA4(insn_t * insnAddress, int majorOpcode, int minorOpcode)
{
  int insnMajorOpcode, insnMinorOpcode;
  int64_t insn;

  insn = toInsn0(insnAddress);
  insnMajorOpcode = (insn >> 37) & 0xF;
  insnMinorOpcode = (insn >> 33) & 0x7;
  if ((insnMajorOpcode == majorOpcode) && (insnMinorOpcode == minorOpcode)) return 0;

  insn = toInsn1(insnAddress);
  insnMajorOpcode = (insn >> 37) & 0xF;
  insnMinorOpcode = (insn >> 33) & 0x7;
  if ((insnMajorOpcode == majorOpcode) && (insnMinorOpcode == minorOpcode)) return 1;

  insn = toInsn2(insnAddress);
  insnMajorOpcode = (insn >> 37) & 0xF;
  insnMinorOpcode = (insn >> 33) & 0x7;
  if ((insnMajorOpcode == majorOpcode) && (insnMinorOpcode == minorOpcode)) return 2;
  return -1;
}

char getM15Value(insn_t * insnAddress, int bundleNro)
{
  int64_t insn;
  int i8, i7, i0_6;

  switch (bundleNro)
    {
    case 0: insn = toInsn0(insnAddress); break;
    case 1: insn = toInsn1(insnAddress); break;
    case 2: insn = toInsn2(insnAddress); break;
    default: printf("Unknow bundle value %d\n", bundleNro); exit(-1);
    }
  i8   = (insn >> 36) & 0x1;
  i7   = (insn >> 27) & 0x1;
  i0_6 = (insn >> 13) & 0x3F;
  return ((i8 << 7) | (i7 << 6) | i0_6);
}

int getA4Value(insn_t * insnAddress, int bundleNro)
{
  int64_t insn;
  int i13, i12_7, i0_6;

  switch (bundleNro)
    {
    case 0: insn = toInsn0(insnAddress); break;
    case 1: insn = toInsn1(insnAddress); break;
    case 2: insn = toInsn2(insnAddress); break;
    default: printf("Unknow bundle value %d\n", bundleNro); exit(-1);
    }
  i13   = (insn >> 36) & 0x1;
  i12_7 = (insn >> 27) & 0x3F;
  i0_6  = (insn >> 13) & 0x7F;
  return ((i13 << 12) | (i12_7 << 6) | i0_6);
}

void setM15Value(insn_t * insnAddress, int bundleNro, char newValue)
{
  int64_t oldInsn, newInsn, tmp;
  int64_t insn0, insn1, insn2;
  int tmpl;
  int i8, i7, i0_6;
  int opcod, x6, hint, r3, qp;

  insn0 = toInsn0(insnAddress);
  insn1 = toInsn1(insnAddress);
  insn2 = toInsn2(insnAddress);
  tmpl = toTemplate(insnAddress);
  switch (bundleNro)
    {
    case 0: oldInsn = insn0; break;
    case 1: oldInsn = insn1; break;
    case 2: oldInsn = insn2; break;
    default: printf("Unknow bundle value %d\n", bundleNro); exit(-1);
    }
  i0_6 = newValue & 0x7F;
  i7   = (newValue >> 0x7) & 0x1;
  i8   = (newValue >> 0x8) & 0x1;

  opcod = (oldInsn >> 37) &   0xF;
  x6    = (oldInsn >> 30) &  0x3F;
  hint  = (oldInsn >> 28) &   0x3;
  r3    = (oldInsn >> 20) &  0x7F;
  qp    = (oldInsn      ) &  0x1F;

  newInsn = 0;
  tmp  = opcod;  newInsn |= (tmp << 37);
  tmp  = i8;     newInsn |= (tmp << 36);
  tmp  = x6;     newInsn |= (tmp << 30);
  tmp  = hint;   newInsn |= (tmp << 28);
  tmp  = i7;     newInsn |= (tmp << 27);
  tmp  = r3;     newInsn |= (tmp << 20);
  tmp  = i0_6;   newInsn |= (tmp << 13);
  tmp  = qp;     newInsn |= (tmp);
#if 0
  toBin (oldInsn, 64);
  toBin (newInsn, 64);
#endif
#define _B(ADDR, TMPL, S0, S1, S2) ({ insn_t myBundle = {(S1) <<46 | (S0) << 5 | TMPL, (S2) << 23 | (S1) >>18 }; *insnAddress = myBundle;})
  switch (bundleNro)
    {
    case 0: _B(insnAddress, tmpl, newInsn,   insn1,   insn2); break;
    case 1: _B(insnAddress, tmpl,   insn0, newInsn,   insn2); break;
    case 2: _B(insnAddress, tmpl,   insn0,   insn1, newInsn); break;
    default: printf("Unknow bundle value %d\n", bundleNro); exit(-1);
    }
}

int main(int argc, char * argv[])
{
  int Ninstructions, i, bundleNro;
  void * myPointer;

  Ninstructions = sizeof (arrayFunction)/16;
  printf("Sizeof long long %d\n", (int) sizeof (long long));
  printf("Sizeof int64_t %d\n", (int) sizeof (int64_t));
  printf("%d instructions in function\n", Ninstructions);
  for (i = 0; i < Ninstructions; ++i)
    {
      myPointer = (void *)&arrayFunction[i][0];
      /*      bundleNro = WhichBundleM14(myPointer, 0x7, 0x2C); M14 lfetch  */
      bundleNro = WhichBundleA4(myPointer, 0x8, 0x4); /* A4 add imm14  */
      if (-1 != bundleNro)
	{
#if 1
	  printf("Insn Nr %d template %s bundle nr %d value %d\n", 
		 i, 
		 ia64_template[toTemplate(myPointer)], 
		 bundleNro, 
		 getA4Value(myPointer, bundleNro)
		 );
#endif
	  setM15Value(myPointer, bundleNro, 255);
	}
    }
  return 0;
}
