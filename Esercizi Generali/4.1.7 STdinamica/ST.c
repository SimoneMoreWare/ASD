#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ST.h"

typedef struct node *link;

struct node { Item val; link next; } ;

typedef struct { link head; link tail; } list;

struct symboltable { list tab; };

static link NEW (Item val, link next) {
  link x;
  x = (link) malloc(sizeof *x);
  if (x == NULL)
    return NULL;
  x->val = val;
  x->next = next;
  return x;
}

ST STinit(int maxN) {
  ST st;
  st = malloc(sizeof(*st));
  if (st == NULL) {
    printf("Memory allocation error\n");
    return NULL;
  }
  st->tab.head = st->tab.tail = NULL;
  return st;
}

void STfree(ST st) {
  link iter, toBeDeleted;
  for (iter = st->tab.head; iter != NULL;) {
    toBeDeleted = iter;
    ITEMfree(toBeDeleted->val);
    iter = iter->next;
    free(toBeDeleted);
  }
  free(st);
}

void STinsert(ST st, Item val) {
  if (st == NULL)
    return;
  if (st->tab.head == NULL)
    st->tab.head = st->tab.tail = NEW(val, NULL);
    if (st->tab.head == NULL) exit(-1);
  else {
    st->tab.tail->next = NEW(val, NULL);
    if (st->tab.head->next == NULL) exit(-1);
    st->tab.tail = st->tab.tail->next;
  }
}

ST STload(FILE *fin) {
  int n, i;
  ST st;
  Item val;

  fscanf(fin, "%d", &n);
  st = STinit(n);
  if (st == NULL) return NULL;
  for (i=0; i<n; i++) {
    val = ITEMscan(fin);
    if (val == NULL) return NULL;
    STinsert(st, val);
  }
  return st;
}

int STsearch(ST st, Key k) {
  link iter;
  if (st == NULL)
    return -1;
  if (st->tab.head == NULL)
    return -1;

  iter = st->tab.head;
  for (iter = st->tab.head; iter != NULL; iter = iter->next) {
    if (KEYcompare(k, KEYget(iter->val)) == 0)
      return 1;
  }
  return -1;
}

void STstore(FILE *fout, ST st) {
  link iter;
  if (st == NULL)
    return;
  if (st->tab.head == NULL)
    return;
  for (iter = st->tab.head; iter != NULL; iter = iter->next)
    ITEMstore(fout, iter->val);
}

void STdelete(ST st, Key k) {
  link iter, prev, toBeDeleted;
  if (st == NULL)
    return;
  if (st->tab.head == NULL)
    return;
  iter = st->tab.head;
  prev = NULL;
  toBeDeleted = NULL;

  for (iter = st->tab.head; iter != NULL; prev = iter, iter = iter->next) {
    if (KEYcompare(k, KEYget(iter->val)) == 0) {
      toBeDeleted = iter;
      if (prev == NULL) {
        st->tab.head = iter->next;
        break;
      } else if (iter->next == NULL) {
        st->tab.tail = prev;
        prev->next = NULL;
        break;
      } else {
        prev->next = iter->next;
        break;
      }
    }
  }

  if(toBeDeleted != NULL) {
    ITEMfree(toBeDeleted->val);
    free(toBeDeleted);
  }
}
