/* Common definitions for lexers */

void errormsg(char *Msg)
{
  fprintf(stderr, "%s\n", Msg);
  exit(0);
}

char *eatPar(char *token)
{
  char *tmp = malloc(1024);
  int i, in = 0;
  char c;
  
  i = strlen (token);
  bcopy (token, tmp, i);
  clearerr(yyin);
  c = input ();
  while (!(0 == in && c == ')') && !feof(yyin) && (i < 1024))
    {
      if ('(' == c) in ++;
      if (')' == c) in --;
      tmp[i++] = c;
      c = input ();
    }
  if (feof(yyin)) errormsg("End of file during parenthesis searching");
  if (i >= 1024)  errormsg("Buffer size too small");
  tmp[i++] = ')';
  tmp[i++] = '\0';
  return tmp;
} /* eatPar */

char *eatProc()
{
  char *tmp = malloc(1024);
  int i;
  char c;
  
  (void) printf("Coucou\n");
  i = 0;
  clearerr(yyin);
  c = input ();
  while ((c != '\n') && !feof(yyin) && (i < 1024))
    {
      tmp[i++] = c;
      c = input ();
    }
  if (feof(yyin)) errormsg("End of file during .proc searching");
  if (i >= 1024)  errormsg("Buffer size too small");
  unput('\n');
  tmp[i++] = '\0';
  return tmp;
} /* eatProc */


void eatComm()
{
  char c;
  
  clearerr(yyin);
  c = input ();
  while ((c != '\n') && !feof(yyin))
    {
      c = input();
    }
  if (feof(yyin)) errormsg("End of file during comment searching");
} /* eatComm */

char *rmPar(char *str)
{
  int i;
  if(str[0] == '('){
     for(i=1; str[i] != 0; i++){
        str[i-1] = str[i];
     } 
     str[i-2] = 0;
  }
  return str;
} /* rmPar */

int yywrap(void) {    return 1; }

