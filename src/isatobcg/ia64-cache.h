#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>

static void iflush(insn *addr, insn *last)
{
  long pageSize= getpagesize();
  long size = last - addr;
  void *ptmp= (char *)((long)addr & ~(pageSize - 1));
  
#if 0
  printf("iflush:  page size %d frontiere %p\n", pageSize, ptmp);
#endif
  ia64_addInsn(ia64_nop[ia64_UnitI], 0);
  ia64_addInsn(ia64_nop[ia64_UnitI], 0);
#if 0
  while(addr <= last)
    {
      asm volatile("fc %0": :"r"(addr));
      ++addr;
    }
  asm volatile("sync.i ;;");
  asm volatile("srlz.i ;;");
#endif
  if (mprotect(ptmp, size, PROT_READ | PROT_WRITE | PROT_EXEC))
    {
      perror("iflush: mprotect");
      return;
    }
}

