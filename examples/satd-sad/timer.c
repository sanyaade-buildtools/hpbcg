/* Copyright (c) 2006 Henri-Pierre Charles. Tous droits reserves */

#ifdef __ECC
unsigned __int64 __getReg (int whichReg);
#pragma intrinsic(__getReg);
#define INL_REGID_APITC 3116 
#endif       

long timer_start ()
{
#if 0
#ifdef __ECC
  return __getReg (INL_REGID_APITC);
#else
  long result;
  __asm__ __volatile__("mov %0=ar.itc" : "=r"(result) :: "memory");
  while (__builtin_expect ((int) result == -1, 0))
    __asm__ __volatile__("mov %0=ar.itc" : "=r"(result) ::"memory");
  return result;
#endif
#endif
} 


long timer_stop ()
{
#if 0
#ifdef __ECC
  return __getReg (INL_REGID_APITC);
#else
  long result;
  __asm__ __volatile__("mov %0=ar.itc" : "=r"(result) :: "memory");
  while (__builtin_expect ((int) result == -1, 0))
    __asm__ __volatile__("mov %0=ar.itc" : "=r"(result) ::"memory");
  return result;
#endif
#endif
}   
