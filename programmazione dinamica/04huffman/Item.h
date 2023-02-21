#ifndef ITEM_H
#define ITEM_H

#define MAXC 11

typedef struct { char let[MAXC]; int freq; } Item;

typedef char *Let;

Item ITEMscan();
void ITEMstore(Item val);
Item ITEMmerge(Item val1, Item val2);
int  ITEMgt(Item val1, Item val2);
int  ITEMlt(Item val1, Item val2);
Let  LETget(Item *pval);

#endif
