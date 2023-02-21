#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#define MAXC 10

typedef struct {
  char name[MAXC];
  int value;
} Item;

typedef int Key;

Item ITEMscan();
Item ITEMrand();
void ITEMstore(Item val);
int  ITEMcheckNull(Item val);
Item ITEMsetNull();
Key  KEYget(Item val);
int  KEYcmp(Key k1, Key k2);

#endif

