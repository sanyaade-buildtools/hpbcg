#include <stdio.h>
#include <malloc_align.h>
#include <free_align.h>
#include <spu_mfcio.h>

#include "mandelbrot-common.h"

vector unsigned int masques[] = 
{
  { 0x00010203, 0x04050607, 0x00010203, 0x04050607}, /* 0 : Complex duplication */
  { 0x00010203, 0x00010203, 0x04050607, 0x04050607}, /* 1 : Complex inverted duplication */
  { 0x0c0d0e0f, 0x08090a0b, 0x80808080, 0x80808080}, /* 2 : Complex realigment */
  { 0x04050607, 0x80808080, 0x80808080, 0x80808080}, /* 3 : Complex module */
  { 0xbf800000, 0x3f800000, 0x00000000, 0x00000000}, /* 4 : -1.0, 1.0, X, X */
  { 0x40800000, 0x3f800000, 0x00000000, 0x00000000}, /* 5    4..0, 0 , 0, 0 */
};

#define SIZE 1024		/* Binary code size */
typedef vector float (*fadd_ptr)(vector float, vector unsigned *);

int main(unsigned long long speid,
	 unsigned long long argp,
	 unsigned long long envp)
{
   char *functionBuffer;
   int mask = 2;
   vector float inParam, res;
   tComplexUnion msg;
   functionBuffer = _malloc_align(SIZE,7); 	 /* Alloc memory for function     */
   mfc_get(functionBuffer, argp, SIZE, 1, 0, 0); /* Read binary code from memory  */
   mfc_write_tag_mask(mask); 
   mfc_read_tag_status_all();

   while (1)
     {
       msg.u.intValues[0] = spu_read_in_mbox();   /* Get parameter */
       msg.u.intValues[1] = spu_read_in_mbox(); 
       inParam[0] = msg.u.complexValues.re;
       inParam[1] = msg.u.complexValues.im;
       inParam[3] = 0;
       inParam[4] = 0;
       res = ((fadd_ptr)functionBuffer)(inParam, masques); /* Run code */
       // printf("%2.2f %2.2f %2.2f %2.2f\n", res[0], res[1], res[2], res[3]);
       msg.u.complexValues.re = res[0];
       msg.u.complexValues.im = res[1];
       spu_write_out_intr_mbox(msg.u.intValues[0]);		/* Send results */
       spu_write_out_intr_mbox(msg.u.intValues[1]);		
       msg.u.complexValues.re = res[2];
       msg.u.complexValues.im = res[3];
       spu_write_out_intr_mbox(msg.u.intValues[0]);		/* Send results */
       spu_write_out_intr_mbox(msg.u.intValues[1]);		
     }
   _free_align(functionBuffer);
   return 0;
}
