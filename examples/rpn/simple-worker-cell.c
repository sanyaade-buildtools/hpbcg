#include <stdio.h>
#include <malloc_align.h>
#include <free_align.h>
#include <spu_mfcio.h>

#define SIZE 1024		/* Binary code size */

typedef int (*fadd_ptr)(int);

int main(unsigned long long speid,
	 unsigned long long argp,
	 unsigned long long envp)
{
   char *functionBuffer;
   int mask = 2;
   int res, a, i, limit;

   functionBuffer = _malloc_align(SIZE,7); 	/* Alloc memory for function */
   mfc_get(functionBuffer, argp, SIZE, 1, 0, 0);/* Read binary code from ppc */
   mfc_write_tag_mask(mask); 
   mfc_read_tag_status_all();

   limit = spu_read_in_mbox(); 
   for (i = 0; i < limit; ++i)
     {
       a = spu_read_in_mbox();   		/* Read parameter */
       res = ((fadd_ptr)functionBuffer)(a);	/* Run code */
       spu_write_out_intr_mbox(res);		/* Send result */
     }
   _free_align(functionBuffer);
   return 0;
}
