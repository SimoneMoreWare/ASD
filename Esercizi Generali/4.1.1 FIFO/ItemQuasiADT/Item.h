#ifndef _ITEM_INCLUDED
#define _ITEM_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#define MAXC 50

typedef struct item {
    char str[MAXC];
    int num;
} Item;

int  ITEMscan(FILE *fp, Item *dp);
int  ITEMcompare(Item d1, Item d2, int campo);
void ITEMstore(FILE *fp, Item d);
void ITEMfree(Item d);

#endif
