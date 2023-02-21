#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>

#define SERV 31
#define CCLI 11


typedef struct {
  int prio;
  char serv[SERV], ccli[CCLI];
} Item;

typedef int Key;

Item ITEMscan(FILE *fin);
int  ITEMgreater(Item val1, Item val2);
void ITEMstore(FILE *fout, Item val);
Item ITEMsetNull();
Key  KEYget(Item val);

#endif


