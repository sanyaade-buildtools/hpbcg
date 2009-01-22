


enum LISTARCHID {ARCH0 = 0, ARCHia64, ARCHcell};
#define ARCHITEM(NAME) {ARCH##NAME, #NAME}
typedef struct 
  {
    int archID;
    char *archName;
  } sArchItem;

int getArchType(char *archName);
