#ifndef ITEM_H_DEFINED
#define ITEM_H_DEFINED

#define MAXC 10

typedef struct {
  char name[MAXC];
  int prio;
} Item;

typedef int Key;

Item ITEMscan();
void ITEMstore(Item val);
Key  KEYget(Item val);
int  KEYcmp(Key k1, Key k2);

#endif

