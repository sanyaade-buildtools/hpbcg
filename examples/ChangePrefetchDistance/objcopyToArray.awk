#!/usr/bin/awk -f
BEGIN{ACCOLADE = 0;}
{
    if (0 == NF) printf("");
    else 
    {
	printf("/* %s */", $1);
	i = 2;
	while (match($i, "^[0-9a-f][0-9a-f]$"))
	       {
		   if (0 == ACCOLADE)	printf("{");
		   printf("0x%s, ", $i);
		   ACCOLADE ++;
		   if (16 == ACCOLADE)
		   {
		       ACCOLADE = 0;
		       printf("}, ");
		   }
		   i++;
	       }
	printf("/*");
	for (; i <= NF ;i++)
	    printf(" %s, ", $i);
	printf("*/\n");
    }	
}