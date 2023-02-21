#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>

#define MAXC 11

typedef struct item* Item;
typedef char *Key;

Item ITEMnew();
void ITEMfree(Item val);
Item ITEMscan(FILE *fin);
void ITEMstore(FILE *fin, Item val);
int  ITEMcompare (Item val1, Item val2);
Item ITEMsetNull();
int  ITEMcheckNull(Item val);


Key   KEYscan();
void  KEYfree();
char *KEYdisplay(Key k);
int   KEYcompare(Key k1, Key k2);
Key   KEYget(Item val);

#endif

