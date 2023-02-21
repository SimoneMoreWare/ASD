#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>

#define MAXC 31
#define MAXK 11

typedef struct item* Item;
typedef char *Key;

Item ITEMnew();
void ITEMfree(Item val);
Item ITEMscan(FILE *fin);
void ITEMstore(FILE *fin, Item val);
int  ITEMcompare (Item val1, Item val2);
void ITEMfree(Item val);
Item ITEMsetNull();

int  KEYcompare(Key k1, Key k2);
Key  KEYscan();
void KEYfree(Key k);
Key  KEYget(Item val);

#endif

