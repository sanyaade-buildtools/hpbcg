/* common.h */



enum LISTARCHID {ARCH0 = 0, ARCHia64, ARCHcell, ARCHarmthumb};
#define ARCHITEM(NAME) {ARCH##NAME, #NAME}
typedef struct 
  {
    int archID;
    char *archName;
  } sArchItem;
enum {TNULL = 0, TINT, TFLT, TBOO, TPRED};
int getArchType(char *archName);
void changeDotByUnder (char *str);
