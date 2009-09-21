#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
  int64_t lo;
  int64_t hi;
} bundle;
typedef bundle insn;


char arrayFunction[][16] =
{
#include "copyItaniumIcc.h"
};

int MyAdd(int a, int b)
{
  return a+b;
} /* MyAdd */

#if 0
       1         1         1
       2         1         0         9         8         7         6         5         4         3         2         1         
76543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210
X           slot 2                      XX         slot 1                        XX         slot 0                        XX   X
X                          hi                                  XX                            lo                                X
#endif
int64_t toInsn0(insn * insnAddress)
{
 insn theBundle;
 
 int64_t insn0;
 theBundle = * insnAddress;
 insn0 = (theBundle.lo >> 5) & 0x1FFFFFFFFFFLL; /* 41 bits i0 */
 return insn0;
}

int64_t toInsn1(insn * insnAddress)
{
 insn theBundle;
 
 int64_t tmp1, tmp2;
 theBundle = * insnAddress;
 tmp1  = (theBundle.hi & 0x7FFFFFFLL);   /* 23 bits in hi */
 tmp2 = (theBundle.lo >> 46 ) & 0x3FFFF; /* 18 bits in hi */
 return ((tmp1 << 18) | tmp2);
}

int64_t toInsn2(insn * insnAddress)
{
 insn theBundle;
 
 int64_t insn2;
 theBundle = * insnAddress;
 insn2 = (theBundle.hi >> 24) & 0x1FFFFFFFFFFLL; /* 41 bits i2 */
 return insn2;
}

int64_t toTemplate(insn * insnAddress)
{
  insn theBundle;
  int template;

  theBundle = * insnAddress;
  template = theBundle.lo & 0x1F; /* 5 bit template */
  return template;
}
void ChangePrefetchDistance (insn * insnAddress, int slotNumber, int PrefetchDistance)
{

} /* ChangePrefetchDistance */

int WhichBundle (insn * insnAddress, int insnCodop, int codopSize)
{
  int insn;
  int mask = (1 << codopSize) - 1;
  (void) printf("Address %p : ", insnAddress);
  insn = (toInsn0(insnAddress) >> (41 -  codopSize)) & mask;
  (void) printf(" 0 : 0x%02X ", insn);
  if (insnCodop == insn) return 0;
  insn = (toInsn1(insnAddress) >> (41 -  codopSize)) & mask;
  (void) printf(" 1 : 0x%02X ", insn);
  if (insnCodop == insn) return 1;
  insn = (toInsn2(insnAddress) >> (41 -  codopSize)) & mask;
  (void) printf(" 2 : 0x%02X\n", insn);
  if (insnCodop == insn) return 2;
  return -1;
}
int main(int argc, char * argv[])
{
  int Ninstructions, i, bundleNro;

  Ninstructions = sizeof (arrayFunction)/16;
  (void) printf("Sizeof long long %d\n", sizeof (long long));
  (void) printf("Sizeof int64_t %d\n", sizeof (int64_t));
  (void) printf("%d instructions in function\n", Ninstructions);
  for (i = 0; i < Ninstructions; ++i)
    {
      bundleNro = WhichBundle(&arrayFunction[i][0], 0x37, 7);
      if (-1 != bundleNro)
	(void) printf("%d %d\n", i, bundleNro);
    }
  return 0;
}
