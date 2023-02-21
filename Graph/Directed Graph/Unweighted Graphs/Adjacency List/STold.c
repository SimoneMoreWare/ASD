#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ST.h"


typedef struct { char *str; } Item;

static char *KEYget(Item data) {
  return data.str;
}

static Item ITEMnew(char *str) {
  Item data;
  data.str = strdup(str);
  return data;
}

static void ITEMfree(Item data) {
    free(data.str);
}

struct symboltable { Item *a; int maxN; int size;};

ST STinit(int maxN) {
  ST st;
  st = malloc(sizeof(*st));
  if (st == NULL) {
    printf("Memory allocation error\n");
    return NULL;
  }
  st->a = malloc(maxN * sizeof(Item) );
  st->maxN = maxN;
  st->size = 0;
  return st;
}

void STfree(ST st) {
  int i;
  for (i = 0; i  < st->size; i++)
    ITEMfree(st->a[i]);
  free(st->a);
  free(st);
}

int STcount(ST st) {
  return st->size;
}

void STinsert(ST st, char *data, int id) {
  if (st->size > st->maxN) {
    st->a = realloc(st->a, (2*st->maxN)*sizeof(Item));
    if (st->a == NULL)
      return;
    st->maxN = 2*st->maxN;
  }
  st->a[id] = ITEMnew(data);
  st->size++;
}

int STsearch(ST st, char *data) {
  int i;
  if (st->size == 0)
    return -1;
  for (i = 0; i  < st->size; i++)
    if (strcmp(data, KEYget(st->a[i]))==0)
      return i;
  return -1;
}

char * STsearchByIndex(ST st, int i){
  return KEYget(st->a[i]);
}

