#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "archId.h"

static sArchItem archList[] =
   {
     ARCHITEM(cell),
     ARCHITEM(ia64),
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


