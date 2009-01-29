/***
 * isatobcg : parser from processor ISA description to multiple
 * formats
 * 
***/
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "isatobcg.h"
#include "common.h"


#define YYSTYPE yystype
  YYSTYPE root;
  extern int yylineno;
  extern char * yytext;
  extern FILE *yyin;
  enum OPTIONS {MACROS = 1, VALID, LIST};
  static int OptionAction;
  static char *IsaName;
  static int IsaType;
  static int IsaLen;
  static InsnList *racineDeListe;
  static InsnList *finDeListe;
%}

%token ARCHNAME, ISALEN REGDb, REGDs, INTb, VAL, SEP, CUT, 
   PRED, INSN, COMM, NL, EQ, COMMA, NEXT, UNK

%%
file: archname insnlist ;
archname: ARCHNAME ISALEN NL 
    {
      IsaName = $1.name;
      IsaLen= $2.val;
      IsaType = getArchType($2.name);
      if (MACROS == OptionAction)
	{
	  printf("/* Autogenerated file, do not edit ! */\n");
	  printf("/* %s %d */\n", IsaName, IsaLen);
	  printf("#include <%s-utils.h>\n", IsaName);
	}
    }
insnlist: insnline | insnline insnlist ;
insnline: NL
    | binpartlist CUT syntaxpart NL {
	  insnAction(&$3, &$1); 
	  if (IsaLen != getLen(&$1))
	    {
	      fprintf(stderr, "Incorrect insn size %s/%s incorrecte : %d\n"
		      "should be %d, line %d\n", 
		      $3.name, IsaName, getLen(&$1), IsaLen, yylineno);
	      exit(-1);
	    }
 	};
binpartlist: 
    binpart { $$ = $1; }
  | binpart binpartlist 
      { 
  	if ( $1.quoi == VAL && $2.quoi == VAL)
	  {
	    $$ = *concat2Val(&$1, &$2); 
	  }
	else
	  {
	    $$ = *dupInsn(&$1);
	    concat(&$$, &$2);
	  }
      }
binpart: VAL | REGDb | INTb | PRED ;

syntaxpart: INSN paramlist { $$ = $1;  concat(&$$, &$2); }
	  | INSN  { $$ = $1; }
paramlist: 
    param { }
  | param operator paramlist { $$ = $1;  concat(&$$, &$3);}

param: REGDs | VAL | INTb ;
operator: COMMA | EQ;
%%

YYSTYPE * dupInsn(YYSTYPE *i)
{
  YYSTYPE *root;
  root = malloc (sizeof (YYSTYPE));
  bcopy (i, root, sizeof (YYSTYPE));
  return root;
} /* dupInsn */

void concat(YYSTYPE * root, YYSTYPE * a2)
{
  YYSTYPE * i;
  for (i = root; i->next ; i = i->next)
    ;
  i->next = dupInsn(a2);
} /* concat */

YYSTYPE * concat2Val(YYSTYPE * a1, YYSTYPE * a2)
{
  YYSTYPE *root;
  root = malloc (sizeof (YYSTYPE));
  bcopy (a2, root, sizeof (YYSTYPE));
  root->quoi = a1->quoi;
  root->len  = a1->len + a2->len;
  root->val  = (a1->val << a2->len) | a2->val;
  return root;
} /* concat2Val */

void printInsn(YYSTYPE *l)
{
  char format[20];
  YYSTYPE *i;
  for (i = l; i ; i = i->next)
    {
      switch (i->quoi)
	{
	case REGDb: 
	  sprintf(format, "R%%%0dd", i->len);
	  printf(format, i->val);
	  break;
	case INTb:  
	  sprintf(format, "I%%%0ds", i->len);
	  printf(format, i->name);
	  break;
	case REGDs: 
	  printf("Rs:%4s ", i->name);
	  break;
	case VAL:  
	  sprintf(format, "V%%%0dd", i->len);
	  printf(format, i->val);
	  break;
	case PRED:
	  sprintf(format, "P%%%0dd", i->len);
	  printf(format, i->val);
	  break;
	case INSN:  
	  printf("I:%8s    ", i->name);
	  break;
	default:
	  printf("Unknown %d\n", i->val);
	  break;
	}
    }
  /* printf("\n"); */
} /* printInsn */


void printQuoi(int quoi)
{
#define PCASE(P) case P: printf("%s\n", #P); break
  switch (quoi)
    {
      PCASE(ARCHNAME);
      PCASE(ISALEN);
      PCASE(REGDb);
      PCASE(REGDs);
      PCASE(INTb);
      PCASE(VAL);
      PCASE(SEP);
      PCASE(CUT);
      PCASE(PRED);
      PCASE(INSN);
      PCASE(COMM);
      PCASE(NL);
      PCASE(EQ);
      PCASE(COMMA);
      PCASE(NEXT);
      PCASE(UNK);
    default: 		printf("Syntax error\n"); exit (-1); break;
    }
#undef PCASE
} /* printQuoi */

char getLetterFromToken(YYSTYPE *t)
{
  char l = 'X';
  switch (t->quoi)
    {
    case INSN:  l = 'i';  break;
    case REGDs: 
    case REGDb: 
      {
	if (0 == strcmp ("ar.pfs", t->name))  break;
	switch (t->name[0])
	  {
	  case 'r': case 'R':  l = 'R';  break;
	  case 'b': case 'B':  l = 'B';  break;
	  case 'f': case 'F':  l = 'F';  break;
	  default: l = 'R';  break;
	  }      
      }
      break;
    case INTb:  l = 'I'; break;
    case VAL:   l = 'V'; break;
    default: break;
    }
  return l;
}

char * buildDescRegFromSyntax(YYSTYPE *l)
{
  YYSTYPE *i;
  int len = 0;
  char *desc, *tmp;
  for (i = l; i ; i = i->next)
    {
      switch (i->quoi)
	{
	case INSN: 
	case REGDs:
	case INTb:
	  len++; break;
	default: break;
	}
    }
  desc = malloc(len+2);		/* _ et \0 */
  tmp = desc;
  *tmp = '_';
  tmp++;
  for (i = l; i ; i = i->next)
    *(tmp++)  = getLetterFromToken(i);
  *tmp = '\0';
  return desc;
}


char * buildDescRegFromBin(YYSTYPE *l)
{
  YYSTYPE *i;
  int len = 0;
  char *desc, *tmp;
  for (i = l; i ; i = i->next)
    {
      switch (i->quoi)
	{
	case INSN: 
	case REGDb:
	case INTb:
	  len++; break;
	default: break;
	}
    }
  desc = malloc(len+2);		/* _ et \0 */
  tmp = desc;
  *tmp = '_';
  tmp++;
  for (i = l; i ; i = i->next)
      *(tmp++)  = getLetterFromToken(i);
  *tmp = '\0';
  return desc;
}

void printInsnName(YYSTYPE *l)
{
  char *desc;

  assert(INSN == l->quoi);
  desc = buildDescRegFromSyntax(l);
  changeDotByUnder (l->name);
  printf("%s%s\n", l->name, desc);
} /* printInsnName */

char *cutRegName(char * in)
{
  int len, k, j;
  char *regName;

  len = strlen(in);
  regName = malloc(len);
  for (j = k = 0; (in[k] != '_') && (k < len) ; ++k)
    {
      regName[j++] = in[k];
    }
  regName[j] = '\0';
  return regName;
} /* cutRegName */
/*
 * iX_Y-Z : Bits Y to Z from the iX value
 * iX_Y : Left Bit Y from iX value
 */
char *cutValName(char * in)    
{
  int len, i, k, j;
  int from, to, dummy;
  char *regName, *result;;

  from = to = dummy = -1;
  len = strlen(in);
  regName = malloc(len);
  for (j = k = 0; (in[k] != '_') && (k < len) ; ++k)
    {
      regName[j++] = in[k];
    }
  regName[j] = '\0';
  sscanf(in, "i%d_%d-%d", &dummy, &to, &from);
  /*   printf("CutvalName %s regName %s from %d to %d\n", in, regName, from, to); */
  result = malloc (100);
  if (-1 == from)
    sprintf (result, "((%s >> %d) & 1)", regName, to);
  else
    {
      dummy = 0;
      for (i = from; i <= to ; ++i)
	{
	  dummy |= (1UL << i);
	}
      sprintf (result, "(%s & 0x%x)", regName, dummy);
    }
  return result;
} /* cutValName */

void printInsnMacro(YYSTYPE *i)
{
  char * name;
  YYSTYPE *j;

  if (!i) return;
  printf("ADDINSN(");
  for (j = i; j ; j = j->next)
    {
      if ((INTb == j->quoi) || (VAL == j->quoi)
	  || (REGDb == j->quoi)	  || (PRED == j->quoi))
	printf("(");
    }
  for (j = i; j ; j = j->next)
    {
      switch (j->quoi)
	{
	case INTb:  
	  if (j != i)
	    { 
	      printf("<< %d | ", j->len); 
	    }
	  name = cutValName(j->name);
	  printf(" LENOK(%s, %d) )", name, j->len);
	  break;
	case VAL:  
	  if (j != i)
	    { 
	      printf("<< %d | ", j->len); 
	    }
	  printf(" LENOK(%d, %d) )", j->val, j->len);
	  break;
	case REGDb: 
	case PRED: 
	  if (0 == strcmp ("ar.pfs", j->name))
	    break;
	  if (j != i){ 
	    printf("<< %d | ", j->len);
	  }
	  name = cutRegName(j->name);
	  printf(" LENOK(%s, %d) )", name, j->len);
	  break;
	default:   break;
	}
    }
  if (ARCHia64 == IsaType)
    {
      printf(", STOP)");
    }
  else
    {
      printf(")");
    }
} /* printInsnMacro */

/* Print an instruction as a function */
void printInsnFunction(YYSTYPE *i)
{
  char * name;
  YYSTYPE *j;

  if (!i) return;
  printf("ADDINSN(");
  for (j = i; j ; j = j->next)
    {
      if ((INTb == j->quoi) || (VAL == j->quoi)
	  || (REGDb == j->quoi)	  || (PRED == j->quoi))
	printf("(");
    }
  for (j = i; j ; j = j->next)
    {
      switch (j->quoi)
	{
	case INTb:  
	  if (j != i) printf("<< %d | ", j->len);
	  name = cutValName(j->name);
	  printf(" LENOK(%s, %d) )", name, j->len);
	  break;
	case VAL:  
	  if (j != i) printf("<< %d | ", j->len);
	  printf(" LENOK(%d, %d) )", j->val, j->len);
	  break;
	case REGDb: 
	case PRED: 
	  if (j != i) printf("<< %d | ", j->len);
	  name = cutRegName(j->name);
	  printf(" LENOK(%s, %d) )", name, j->len);
	  break;
	default:   break;
	}
    }
  if (ARCHia64 == IsaType)
    printf(", STOP)\n");
  else
    printf(")");
} /* printInsnFunction */

void printArmThumbInsnDesc(YYSTYPE *syntax, YYSTYPE *bin)
{
  YYSTYPE *i;
  int isFirst = 1;

  printf("#define %s(", syntax->name);
  for (i = syntax; i ; i = i->next)
    {
      printQuoi (i->quoi);
    }

  printf("%c QP, STOP)\t", (isFirst)?' ':',');
  /* printInsn(bin); */

} /* printArmThumbInsnDesc */

void printIa64InsnMacroDesc(YYSTYPE *syntax, YYSTYPE *bin)
{
  char * desc;
  YYSTYPE *i;
  int isFirst = 1;

  desc = buildDescRegFromSyntax(syntax);
  changeDotByUnder(syntax->name);
  printf("#define %s%s(", syntax->name, desc);
  for (i = syntax; i ; i = i->next)
    {
      switch (i->quoi)
	{
	case REGDs: 
	case INTb:  
	  if (0 == strcmp ("ar.pfs", i->name))	    break;
	  if (isFirst) isFirst = 0; else printf(" ,");
	  printf("%s", i->name); 
	  break;
	case VAL:  
	  if (isFirst) isFirst = 0; else printf(" ,");
	  printf("V"); 
	  break;
	default: break;
	}
    }

  printf("%c QP, STOP)\t", (isFirst)?' ':',');
  /* printInsn(bin); */
  printInsnMacro(bin);
  printf("\n");
  free(desc);
} /* printIa64InsnMacroDesc */


void printIa64InsnFunctDesc(YYSTYPE *syntax, YYSTYPE *bin)
{
  char * desc;
  YYSTYPE *i;
  int isFirst = 1;

  desc = buildDescRegFromSyntax(syntax);
  changeDotByUnder(syntax->name);
  printf("void %s%s(", syntax->name, desc);
  for (i = syntax; i ; i = i->next)
    {
      switch (i->quoi)
	{
	case REGDs: 
	case INTb:  
	  if (0 == strcmp ("ar.pfs", i->name))	    break;
	  if (isFirst) isFirst = 0; else printf(" ,");
	  printf("int %s", i->name); 
	  break;
	case VAL:  
	  if (isFirst) isFirst = 0; else printf(" ,");
	  printf("int V"); 
	  break;
	default: break;
	}
    }
  printf("%c int QP, int STOP){\t", (isFirst)?' ':',');
  printInsnMacro(bin);
  printf(";\t}\n");
  free(desc);
} /* printIa64InsnMacroDesc */


/* Define a cell instruction as a macro instruction */
void printCellInsnMacroDesc(YYSTYPE *syntax, YYSTYPE *bin)
{
  char * desc;
  YYSTYPE *i;
  int isFirst = 1;
  /* printInsn(syntax); */
  desc = buildDescRegFromSyntax(syntax);
  changeDotByUnder(syntax->name);
  printf("#define %s%s(", syntax->name, desc);
  for (i = syntax; i ; i = i->next)
    {
      if (! isFirst)
	{
	  printf(",");
        }
      switch (i->quoi)
	{
	case REGDs: 
	case INTb:  
	  isFirst = 0;
	  printf("%s", i->name); 
	  break;
	case VAL:  
	  isFirst = 0;
	  printf("V"); 
	  break;
	default: break;
	}
    }
  printf(")\t");
  printInsnMacro(bin);
  printf("\n");
  free(desc);
} /* printCellInsnMacroDesc */

/* Define a cell instruction as a function */
void printCellInsnFunctDesc(YYSTYPE *syntax, YYSTYPE *bin)
{
  char * desc;
  YYSTYPE *i;
  int isFirst = 1;
  /* printInsn(syntax); */
  desc = buildDescRegFromSyntax(syntax);
  changeDotByUnder(syntax->name);
  printf("void %s%s\t(", syntax->name, desc);
  for (i = syntax; i ; i = i->next)
    {
      if (! isFirst)
	printf(",");
      switch (i->quoi)
	{
	case REGDs: 
	case INTb:  
	  isFirst = 0;
	  printf("int %s", i->name); 
	  break;
	case VAL:  
	  isFirst = 0;
	  printf("int V"); 
	  break;
	default: break;
	}
    }
  printf("){\t");
  /* printInsn(bin); */
  printInsnFunction(bin);
  printf(";\t}\n");
  free(desc);
} /* printCellInsnFunctDesc */

/* What the bits lenght of an INSN */
int getLen(YYSTYPE *l)
{
  YYSTYPE *i;
  int len = 0;
  for (i = l; i ; i = i->next)
      len += i->len;
  return len;
} /* getLen */

/* Add the new instruction at the end of the list */
void insnAction(YYSTYPE *syntax, YYSTYPE *bin)
{
  InsnList *tmp;
  YYSTYPE *s, *b;
  tmp = malloc (sizeof (InsnList));
  s = malloc (sizeof (YYSTYPE));
  b = malloc (sizeof (YYSTYPE));
  bcopy (syntax, s, sizeof (YYSTYPE));
  bcopy (bin,    b, sizeof (YYSTYPE));
  tmp -> binpart = b;
  tmp -> syntaxpart = s;
  if (NULL == racineDeListe)
      finDeListe = racineDeListe = tmp;
  else
    {
      finDeListe->next = tmp;
      finDeListe = tmp;
      tmp -> next = NULL;
    }
}

void yyerror(char *s) 
{
  fprintf(stderr, "Line %d: %s\n", yylineno, s);
  fprintf(stderr, "Token %s\n", yytext);
  exit(-1);
}


int main(int argc, char * argv[])
{
  int i;
  InsnList *itmp;
  YYSTYPE *syntax, *bin;

  OptionAction = MACROS;
  for (i = 1; i < argc ; ++i)
    {
      if ('-' == argv[i][0])
	switch (argv[i][1])
	  {
	  case 'd':	yydebug = 1; break;
	  case 'm':	OptionAction = MACROS; break;
	  case 'l':	OptionAction = LIST; break;
	  case 'v':    	OptionAction = VALID;  break;
	  default:     	printf("%s -[m|v|d] [File]\n", argv[0]);
	    		exit(0);
	  }
      else
	{
	  FILE * myin;
	  
	  if ((myin = fopen (argv[i], "r")))
	    yyin = myin;
	  else
	    yyin = stdin;
	}
    }
  yyparse();
  switch (OptionAction)
    {
#if 0
    case VALID:  
      printInsn(syntax); printf(" | "); printInsn(bin); 
      printf("\n"); 
      break;
#endif
    case MACROS:
      printf("#ifndef WITHOUT_HPBCG_MACROS\n");
      for (itmp = racineDeListe; itmp->next; itmp = itmp->next)
	{
	  syntax = itmp->syntaxpart;
	  bin = itmp->binpart;
	  switch (IsaType)
	    {
	    case ARCHia64: printIa64InsnMacroDesc(syntax, bin); break;
	    case ARCHcell: printCellInsnMacroDesc(syntax, bin); break;
	    default: fprintf(stderr, "Arch %d not known\n", IsaType);  
	      exit (-1); break;
	    }
	}
      printf("#else /* WITH_HPBCG_MACROS */\n");
      for (itmp = racineDeListe; itmp->next; itmp = itmp->next)
	{
	  syntax = itmp->syntaxpart;
	  bin = itmp->binpart;
	  switch (IsaType)
	    {
	    case ARCHcell:  printCellInsnFunctDesc(syntax, bin); break;
	    case ARCHia64:  printIa64InsnFunctDesc(syntax, bin); break;
	    default: fprintf(stderr, "Arch %d not known\n", IsaType);  
	      	exit (-1); break;
	    }
	}
      printf("#endif /* WITH_HPBCG_MACROS */\n");
      break;
    case LIST: 
      for (itmp = racineDeListe; itmp->next; itmp = itmp->next)
	{
	  syntax = itmp->syntaxpart;
	  printInsnName(syntax); 
	}
      break;
    default: 
      printf("Error action inconnue %d\n", OptionAction);
      break;
    }
  return 0;
} /* main */
