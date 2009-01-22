/* Copyright (c) 2008 Henri-Pierre Charles. Tous droits reserves */

/***
   NOM
     IsatoBCG
   UTILITE
     
   NOTES
     $Revision$
     
   HISTOIRE
          hpc - May 20, 2008: Created.
     $Log$
***/

void yyerror(char *);
int yylex(void);
int yyparse(void);
typedef struct yy
{
  int quoi;
  int len;
  int val;
  char *name;
  struct yy *next;
} yystype;

typedef struct zz
{
  struct yy *binpart;
  struct yy *syntaxpart;
  struct zz *next;
} InsnList;

