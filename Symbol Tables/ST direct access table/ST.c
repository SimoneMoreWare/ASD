#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "ST.h"

struct symbtab { Item *a; int M; int N;};

ST STinit(int maxN) {
  int i;
  ST st;
  st = malloc(sizeof(*st));
  if (st == NULL) {
    printf("Memory allocation error\n");
    return NULL;
  }
  st->a = malloc(maxN * sizeof(Item) );
  for (i = 0; i < maxN; i++)
    st->a[i] = ITEMsetNull();
  st->M = maxN;
  st->N = 0;
  return st;
}

void STfree(ST st) {
  free(st->a);
  free(st);
}

int STcount(ST st) {
  return st->N;
}

void STinsert(ST st, Item val) {
  int index = GETindex(KEYget(&val));
  st->a[index] = val;
  st->N++;
}

Item STsearch(ST st, Key k) {
  int index = GETindex(k);
return st->a[index];
}

void STdelete(ST st, Key k) {
  st->a[GETindex(k)] = ITEMsetNull();
  st->N--;
}

Item STselect(ST st, int r) {
  int i;
  for (i = 0; i < st->M; i++)
    if ( (ITEMcheckNull(st->a[i])==0) && (r-- == 0))
      return st->a[i];
  return ITEMsetNull();
}

void STdisplay(ST st){
  int i;
  for (i = 0; i < st->M; i++)
    if (ITEMcheckNull(st->a[i]) == 0)
      ITEMstore(st->a[i]);
}
