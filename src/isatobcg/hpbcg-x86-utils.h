/*
 * hpbcg-x86-utils.h
 *
 */

#include <hpbcg-asm-common.h>
#include <sys/mman.h>
#include <unistd.h>

static void hpbcg_x86_addInsn8(u_int64_t insn);
static void hpbcg_x86_addInsn16(u_int64_t insn);
static void hpbcg_x86_addInsn24(u_int64_t insn);
static void hpbcg_x86_addInsn32(u_int64_t insn);
static void hpbcg_x86_addInsn40(u_int64_t insn);

#define ADDINSN8(VAL)  hpbcg_x86_addInsn8(VAL);
#define ADDINSN16(VAL) hpbcg_x86_addInsn16(VAL); 
#define ADDINSN24(VAL) hpbcg_x86_addInsn24(VAL);
#define ADDINSN32(VAL) hpbcg_x86_addInsn32(VAL);
#define ADDINSN40(VAL) hpbcg_x86_addInsn40(VAL);

#define ORG(PTR) (hpbcg_asm_pc = (insn *) PTR)

typedef unsigned char insn;
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

static void hpbcg_x86_addInsn8(u_int64_t insn)
{
  /* printf("hpbcg_x86_addInsn insn %X\n", insn); */
  (*hpbcg_asm_pc++) = insn & 0xFF;
}

static void hpbcg_x86_addInsn16(u_int64_t insn)
{
  hpbcg_x86_addInsn8(insn >> 8);
  hpbcg_x86_addInsn8(insn);
}

static void hpbcg_x86_addInsn24(u_int64_t insn)
{
  hpbcg_x86_addInsn8(insn >> 16);
  hpbcg_x86_addInsn8(insn >> 8);
  hpbcg_x86_addInsn8(insn);
}

static void hpbcg_x86_addInsn32(u_int64_t insn)
{
  hpbcg_x86_addInsn16(insn >> 16);
  hpbcg_x86_addInsn16(insn);
}

static void hpbcg_x86_addInsn40(u_int64_t insn)
{
  hpbcg_x86_addInsn8(insn >> 32);
  hpbcg_x86_addInsn16(insn >> 16);
  hpbcg_x86_addInsn16(insn);
}

static void neverCalled()
{
  u_int64_t myinsn = 0;
  iflush (NULL, NULL);
  hpbcg_x86_addInsn8(myinsn);
  hpbcg_x86_addInsn16(myinsn);
  hpbcg_x86_addInsn24(myinsn);
  hpbcg_x86_addInsn32(myinsn);
  hpbcg_x86_addInsn40(myinsn);
}
