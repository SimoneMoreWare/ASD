#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#define MAXC 11

typedef struct { char name[MAXC]; int size; int value;} Item;

Item ITEMscan();
void ITEMshow(Item x);

#endif

