#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ST.h"
#define MAXC 21

struct symboltable {char **a; int maxN;};

ST STinit(int maxN) {
  int i;
  ST st;
  st = malloc(sizeof(*st));
  if (st == NULL) {
    printf("Memory allocation error\n");
    return NULL;
  }
  st->a = calloc(maxN,sizeof(char *));
  if (st->a == NULL) {
    printf("Memory allocation error\n");
    free(st);
    return NULL;
  }
  st->maxN = maxN;
  for (i=0; i<maxN; i++)
    st->a[i] = NULL;
  return st;
}

void STfree(ST st) {
  int i;
  for (i = 0; i  < st->maxN; i++)
    if (st->a[i]!=NULL)
      free(st->a[i]);
  free(st->a);
  free(st);
}

void STinsert(ST st, char *s, int id) {
  if (id >= st->maxN) {
    printf("Index: %d is too large\n", id);
    return;
  }
  st->a[id] = strdup(s);
}

int STsearch(ST st, char *s) {
  int i;
  for (i = 0; i  < st->maxN; i++)
    if (st->a[i]!=NULL && strcmp(s, st->a[i])==0)
      return i;
  return -1;
}

char *STsearchByIndex(ST st, int i){
  return st->a[i];
}

