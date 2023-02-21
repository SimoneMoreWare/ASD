#include <stdlib.h>
#include <stdio.h>

#include "skilift.h"
#include "ST.h"

struct symbtab {
  skilift *a;
  int maxN;
  int size;
};

ST STinit(int maxN) {
  ST st; int i;
  st = malloc(sizeof(*st));
  st->a = malloc(maxN * sizeof(skilift));
  for (i = 0; i < maxN; i++)
    st->a[i] = SKILIFTNULL();
  st->maxN = maxN;
  st->size = 0;
  return st;
}

int STcount(ST st) {
  return st->size;
}

void STfree(ST st) {
  free(st->a);
  free(st);
}

void STdestroy(ST st) {
  int i;
  for (i = 0; i < st->size; i++)
    SKILIFTfree(st->a[i]);
  free(st->a);
  free(st);
}

void STdisplay(ST st, FILE *fp){
  int i;
  for (i = 0; i < st->size; i++) {
    SKILIFTprint(st->a[i], fp);
    printf("\n");
  }
}

static skilift STinsert(ST st, skilift val) {
  int i = st->size;
  if (st->size >= st->maxN) {
    void *p =realloc(st->a,(2*st->maxN)*sizeof(skilift));
    if (p == NULL)
      return SKILIFTNULL();
    st->a = p;
    st->maxN = 2*st->maxN;
  }
  st->a[i] = val;
  st->size++;
  return val;
}

skilift STsearch(ST st, char *str) {
  int i;
  if (st->size == 0)
    return SKILIFTNULL();
  for (i = 0; i < st->size; i++)
    if (strcmp(str, SKILIFTid(st->a[i]))==0)
      return st->a[i];
  return SKILIFTNULL();
}

skilift STsearchOrInsert(ST st, char *str, int time) {
  skilift s = STsearch(st,str);
  if (s != SKILIFTNULL())
    return s;
  else
    return STinsert(st, SKILIFTnew(str, time, st->size));
}

skilift STsearchByIndex(ST st, int index) {
  if (st->size == 0)
    return SKILIFTNULL();
  if (index >= st->size)
    return SKILIFTNULL();
  return st->a[index];
}

