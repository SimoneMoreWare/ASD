#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#define MAXC 3

typedef struct {
  char name[MAXC];
  int value;
} Item;

typedef char *Key;

Item ITEMscan();
void ITEMstore(Item val);
int  ITEMcheckNull(Item val);
Item ITEMsetNull();
Key  KEYget(Item *pval);
int  KEYcmp(Key k1, Key k2);

#endif


