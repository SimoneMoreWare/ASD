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
    printf("st memory allocation error\n");
    return NULL;
  }
  st->maxN = maxN;
  st->a = (char **)calloc(maxN,sizeof(char *));
  if (st->a == NULL) {
    printf("st->a memory allocation error\n");
    free(st);
    return NULL;
  }
  st->maxN = maxN;
  for (i=0; i<st->maxN; i++)
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

int STinsert(ST st, char *s, int id) {
  if (id >= st->maxN) {
    printf("Index: %d is too large\n", id);
    return -1;
  }
  st->a[id] = strdup(s);
  if (st->a[id] == NULL) exit(-1);
  return id;
}

int STsearch(ST st, char *s) {
  int i;
  for (i = 0; i  < st->maxN; i++)
    if (st->a[i]!=NULL && strcmp(s, st->a[i])==0)
      return i;
  return -1;
}

