/* -*- c -*- */

%{
#include <stdio.h>
#include <string.h>
#include "isatobcg.h"
#include "y.tab.h"


  char *eatPar(char *in);
  char *eatProc();
  void eatComm();

  int btoi(char * chaine);
  yystype yylval;
  int yylineno = 1;
%}
bin [01]+
com #.*$
empty ^[ \t]*$
sep [\[\] \t]
nl  \n
regb [bBpPrRfF][0-9]_[0-9]+(-[0-9]+)?
int [iI][0-9]+(_[0-9]+(-[0-9]+)?)?
regs [bBrRpPfF][0-9]|"pc"|"sp"|"ar.pfs"
insn [a-zA-Z][.a-zA-Z0-9]*
nb   [0-9]+
procname "cell"|"ia64"|"ppc"|"armthumb"|"arm"|"sparc"
%%
{com}		{ yylineno++; eatComm(); }
{sep}+		{ ; }
{bin} 		{ 
  		yylval.val = btoi(yytext); 
  		yylval.len = strlen(yytext);
		yylval.quoi = VAL;
		return VAL; 
		}
[Qq][Pp]	{  
  		   yylval.len = 6;
		   yylval.quoi = PRED;
		   yylval.name = "QP";
		   return PRED; 
		}
"|"		{ return CUT; }
{int}		{ 
  		int id, sup, inf;
		id = sup = inf = -1;
		sscanf(yytext, "i%d_%d-%d", &id, &sup, &inf);
		if (-1 == inf)
		  yylval.len = 1; 
		else
		  yylval.len = sup - inf + 1; 
  		yylval.name = strdup (yytext); 
		yylval.quoi = INTb;
  		return INTb; }
{nl}		{ yylineno++; return NL; }
{regb}		{ 
  		  char format[7];
		  int id, sup, inf;
		  id = sup = inf = -1;
		  sprintf(format, "%c%%d_%%d-%%d", yytext[0]);
		  sscanf(yytext, format, &id, &sup, &inf);
		  if (-1 == inf)
		    yylval.len = sup; 
		  else
		    yylval.len = sup - inf + 1; 
		  yylval.val = id;
  		  yylval.name = strdup (yytext); 
		  yylval.quoi = REGDb;
		  return REGDb; 
		}
{regs}		{ 
  		  yylval.name = strdup (yytext); 
		  yylval.quoi = REGDs;
		  return REGDs; 
		}
{procname}	{ yylval.name = strdup (yytext); 
  		  return ARCHNAME; }
{insn}		{ 
  		  yylval.name = strdup (yytext); 
  		  yylval.quoi = INSN; 
		  return INSN; }
"="		{ return EQ; }
","		{ return COMMA; }
{nb}		{ sscanf(yytext, "%d", &yylval.val);
    		  return ISALEN; 
		}
{empty}		{ yylineno++; eatComm(); }
%%
#if 0
int main(int argc, char * argv[])
{
  int quoi, len = 0;
  while ((quoi =  yylex()))
    {
      switch (quoi)
	{
	case REGDb: 	  len += yylval.len;	  break;
	case VAL: 	  len += yylval.len;	  break;
	case CUT: 	  			break;
	case SEP: 	  			break;
	case PRED:	  len += yylval.len;	  break;
	case INSN: 				break;
	case COMM: 				break;
	case NL: 	  len = 0;	  	break;
	case NEXT:				break;
	case EQ:				break;
	case UNK:				break;
	default: printf("%s : not recognized\n", yytext); break;
	}
    }
  printf("Exit\n");
  return 0;
}
#endif

int btoi(char * chaine)
{
  int tmp = 0;
   while (*chaine)
    {
      tmp <<= 1;
      switch (*chaine)
	{
	case '0': 		break;
	case '1': tmp += 1; 	break;
	default: (void) printf("Error : char %c not in [01]\n", *chaine);
	}
      chaine++;
    }
   return tmp;
} /* btoi */


#include "lexer-common.h"
