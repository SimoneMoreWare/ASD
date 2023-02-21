#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ST.h"

struct symboltable {skilift *a; int maxN; int size;};

static char *key(skilift s) {
    return SKILIFTid(s);
}

ST STinit(int maxN) {
  ST st = malloc(sizeof (struct symboltable));
  if (st == NULL) {
    printf("Errore di allocazione di memoria\n");
    exit(1);
  }
  st->a = (skilift *) calloc (maxN, sizeof (skilift));
  if (st->a == NULL) {
    printf("Errore di allocazione di memoria\n");
    exit(1);
  }
  st->maxN = maxN;
  st->size = 0;
  return st;
}

void STfree(ST st) {
  int id = 0;
  if (st==NULL)
    return;

  for (id=0; id<st->size; id++)
    if (st->a[id] != NULL)
      SKILIFTfree(st->a[id]);
  free(st->a);
  free(st);
}

int STcount(ST st) {
  return st->size;
}

skilift STinsert(ST st, char *str, int time) {
  int id = st->size;
  if (st->size >= st->maxN) {
    st->a = realloc(st->a, (2*st->maxN)*sizeof(skilift));
    if (st->a == NULL) {
      printf("Errore di allocazione di memoria\n");
      exit(1);
    }
    st->maxN = 2*st->maxN;
  }
  st->a[id] = SKILIFTnew(str, time, id);
  st->size++;
  return st->a[id];
}

skilift STsearch(ST st, char *str) {
  int id;
  for (id=0; id<st->size; id++) {
    if (strcmp(str,key(st->a[id]))==0)
      return st->a[id];
  }
  return NULL;
}

skilift STsearchOrInsert(ST st, char *str, int time) {
  skilift s = STsearch(st,str);
  if (s != NULL)
    return s;
  else
    return STinsert(st, str, time);
}

skilift STsearchByIndex(ST st, int index) {
  if (st->size == 0)
    return NULL;
  if (index >= st->size)
    return NULL;
  return st->a[index];
}

