#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#define MAXC 10

typedef struct {
  char name[MAXC];
  int prio;
} Item;

typedef char *Name;

Item ITEMscan();
void ITEMstore(Item val);
Item ITEMsetNull();

Name NAMEget(Item *pval);
int  NAMEcmp(Name n1, Name n2);
int  PRIOget(Item val);


#endif

