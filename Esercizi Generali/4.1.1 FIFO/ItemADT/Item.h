#ifndef _ITEM_INCLUDED
#define _ITEM_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#define MAXC 50

typedef struct item *Item;

int  ITEMscan(FILE *fp, Item *dp);
int  ITEMcompare(Item d1, Item d2, int campo);
void ITEMstore(FILE *fp, Item d);
void ITEMfree(Item d);
Item ITEMnew(char *str, int num);

#endif
