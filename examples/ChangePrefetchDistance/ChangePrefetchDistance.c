/* This function */

typedef struct {
  ui64_t lo;
  ui64_t hi;
} bundle;
typedef bundle insn;

int MyAdd(int a, int b)
{
  return a+b;
} /* MyAdd */

void ChangePrefetchDistance (void * insnAddress, int slotNumber, int PrefetchDistance)
{
  insn theBundle;
  int template;
  ui64_t insn0, insn1, insn2;

  theBundle = insnAddress;
  template = theBundle.lo & 0x1F; /* 5 bit template */
  insn0 = (theBundle.lo >> 5) & 0x1FFFFFFFFFF; /* 41 bits i0 */
  insn1 = (theBundle.hi & 0x3FFFF)		/* High 18 bits i1 */
  insn1 |= (theBundle.lo >> 46) & 0x3FFFF;       /* Low 18 bits i1 */
} /* ChangePrefetchDistance */


int main(int argc, char * argv[])
{
  
}
