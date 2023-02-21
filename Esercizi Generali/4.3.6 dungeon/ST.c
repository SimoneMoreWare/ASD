#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ST.h"
#define MAXC 21

typedef struct { char str[MAXC]; int vs; int ms;  } Room;

struct symboltable {Room *a; int maxN;};

ST STinit(int maxN) {
  ST st;
  st = malloc(sizeof(*st));
  if (st == NULL) {
    printf("Memory allocation error\n");
    return NULL;
  }
  st->a = calloc(maxN,sizeof(Room));
  if (st->a == NULL) {
    printf("Memory allocation error\n");
    free(st);
    return NULL;
  }
  st->maxN = maxN;
  return st;
}

void STfree(ST st) {
  free(st->a);
  free(st);
}

void STinsert(ST st, char *s, int v, int m, int id) {
  if (id >= st->maxN) {
    printf("Index: %d is too large\n", id);
    return;
  }
  strcpy(st->a[id].str, s);
  st->a[id].vs = v;
  st->a[id].ms = m;
}

int STsearch(ST st, char *s) {
  int i;
  for (i = 0; i  < st->maxN; i++)
    if (strcmp(s, st->a[i].str)==0)
      return i;
  return -1;
}

char *STsearchNameByIndex(ST st, int i){
  return st->a[i].str;
}

int STsearchPointsByIndex(ST st, int i){
  return st->a[i].vs;
}

int STsearchValueByIndex(ST st, int i){
  return st->a[i].ms;
}

