#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <stdlib.h>
#define MAXC 6


typedef struct {
  char name[MAXC];
  int start, stop;
  int selected;
} Item;

typedef int Key;

int  ITEMlt(Item A, Item B);
int  ITEMeq(Item A, Item B);
Item ITEMscan();
void ITEMstore(Item A);
Key  KEYgetStart(Item A);
Key  KEYgetStop(Item A);
Key  KEYgetSel(Item A);
void KEYsetSel(Item *pA);
#endif

