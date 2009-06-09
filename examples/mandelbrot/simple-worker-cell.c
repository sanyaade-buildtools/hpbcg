#include <stdio.h>
#include <malloc_align.h>
#include <free_align.h>
#include <spu_mfcio.h>

#include "mandelbrot-common.h"

#define SIZE 1024		/* Binary code size */
typedef vector float (*fadd_ptr)(vector float val);

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
       res = ((fadd_ptr)functionBuffer)(inParam); /* Run code */
       // printf("%2.2f %2.2f %2.2f %2.2f\n", res[0], res[1], res[2], res[3]);
       msg.u.complexValues.re = res[0];  
       msg.u.complexValues.im = res[1];  
       spu_write_out_intr_mbox(msg.u.intValues[0]);		/* Send results */
       spu_write_out_intr_mbox(msg.u.intValues[1]);		
     }
   _free_align(functionBuffer);
   return 0;
}
