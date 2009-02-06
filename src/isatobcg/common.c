/* 
 * common.c 
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "common.h"

void changeDotByUnder (char *str)
{
  int i, l = strlen(str);
  for (i = 0; i < l; ++i)
    {
      if ('.' == str[i])
	str[i] = '_';
    }
} /* changeDotByUnder */

static sArchItem archList[] =
   {
     ARCHITEM(cell),
     ARCHITEM(ia64),
     ARCHITEM(power4),
     ARCHITEM(armthumb),
     ARCHITEM(0)
   };

int getArchType(char *archName)
{
  int i, archType = 0;
  for (i = 0; archList[i].archID; ++i)
    {
      if (0 == strcmp (archName, archList[i].archName))
	archType = archList[i].archID;
    }
  assert (archType != 0);
  return archType;
} /* getArchType */


