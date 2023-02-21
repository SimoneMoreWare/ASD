#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <stdlib.h>
#define MAXC 6

typedef  struct  { char name[MAXC]; float weight; float value; float ratio; float fract; } Item;

typedef float Key;

int    ITEMeq(Item A, Item B);
int    ITEMgt(Item A, Item B);
Item   ITEMscan();
void   ITEMstore(Item A);
Key    KEYgetW(Item A);
Key    KEYgetV(Item A);
Key    KEYgetF(Item A);
void   KEYsetF(Item *pA, float f);
#endif
