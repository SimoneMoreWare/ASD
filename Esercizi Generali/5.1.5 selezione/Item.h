#include <stdio.h>
#include <stdlib.h>
#define maxKey 100

typedef struct { int x; } Item;
typedef int Key;

Key  key(Item x);
Item ITEMscan();
void ITEMshow(Item x);
Item ITEMrand();
int  ITEMeq(Item A, Item B);
int  ITEMneq(Item A, Item B);
int  ITEMlt(Item A, Item B);
int  ITEMgt(Item A, Item B);
