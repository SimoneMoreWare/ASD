#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ST.h"

#define ratio 3

typedef struct STnode* link;
struct STnode { Item val; link next; } ;

struct symboltable { link *heads; int M; link z; };

static link NEW(Item item, link next);
static int hash(Key k, int M);
static Item searchRbyCust(link t, Key k, link z);
static Item searchRbyCat(link t, Key k, link z);
static link deleteRbyCat(link x, Item val);
static link deleteRbyCust(link x, Item val);
static void visitRbyCust(FILE *fout, link h, link z);
static void visitRbyCat(FILE *fout, link h, link z);

static link NEW(Item val, link next) {
  link x = malloc(sizeof *x);
  if (x == NULL) return NULL;
  x->val = val;
  x->next = next;
  return x;
}

ST STinit(int maxN) {
  int i;
  ST st = malloc(sizeof *st);
  if (st == NULL) return NULL;
  st->M = maxN/ratio;
  st->heads = malloc(st->M*sizeof(link));
  if (st->heads == NULL) return NULL;
  st->z = NULL;
  for (i=0; i < st->M; i++)
    st->heads[i] = st->z;
  return st;
}

void STfree(ST st) {
  int i;
  for (i=0; i < st->M; i++) {
    if(st->heads[i]) {
      ITEMfree(st->heads[i]->val);
      free(st->heads[i]);
    }
  }
  free(st->heads);
  free(st);
}

static int hash(Key k, int M) {
  int h = 0, base = 127;
  for ( ; *k != '\0'; k++)
    h = (base * h + *k) % M;
  return h;
}

void STinsertByCust(ST st, Item val) {
  int i;
  i = hash(KEYgetId(&val), st->M);
  st->heads[i] = NEW(val, st->heads[i]);
}

void STinsertByCat(ST st, Item val) {
  int i;
  i = hash(KEYgetCat(&val), st->M);
  st->heads[i] = NEW(val, st->heads[i]);
}


static Item searchRbyCat(link t, Key k, link z) {
  if (t == z)
    return ITEMsetNull();
  if (KEYcompare(KEYgetCat(&(t->val)), k)==0)
    return t->val;
  return
  searchRbyCat(t->next, k, z);
}

Item STsearchByCat(ST st, Key k) {
  return searchRbyCat(st->heads[hash(k, st->M)], k, st->z);
}

static Item searchRbyCust(link t, Key k, link z) {
  if (t == z)
    return ITEMsetNull();
  if (KEYcompare(KEYgetId(&(t->val)), k)==0)
    return t->val;
  return
  searchRbyCust(t->next, k, z);
}

Item STsearchByCust(ST st, Key k) {
  return searchRbyCust(st->heads[hash(k, st->M)], k, st->z);
}

static link deleteRbyCat(link x, Item val) {
  link t;
  if (x == NULL)
    return NULL;
  if (KEYcompare(KEYgetCat(&(x->val)), KEYgetCat(&val))==0){
    t = x->next;
    free(x);
    return t;
  }
  x->next = deleteRbyCat(x->next, val);
  return x;
}

void STdeleteByCat(ST st, Item val) {
  int i;
  i = hash(KEYgetCat(&val), st->M);
  st->heads[i] = deleteRbyCat(st->heads[i], val);
}


static link deleteRbyCust(link x, Item val) {
  link t;
  if (x == NULL)
    return NULL;
  if (KEYcompare(KEYgetId(&(x->val)), KEYgetId(&val))==0){
    t = x->next;
    free(x);
    return t;
  }
  x->next = deleteRbyCust(x->next, val);
  return x;
}

void STdeleteByCust(ST st, Item val) {
  int i;
  i = hash(KEYgetId(&val), st->M);
  st->heads[i] = deleteRbyCust(st->heads[i], val);
}

static void visitRbyCust(FILE *fout, link h, link z) {
  if (h == z)
    return;
  ITEMstoreCust(fout, h->val);
  visitRbyCust(fout, h->next, z);
}

void STlistByCust(FILE *fout, ST st) {
  int i;
  for (i=0; i < st->M; i++)
    if (st->heads[i] != NULL)
      visitRbyCust(fout, st->heads[i], st->z);
}

static void visitRbyCat(FILE *fout, link h, link z) {
  listLink t;
  if (h == z)
    return;
  ITEMstoreCat(fout, h->val);
  for (t=h->val.customerList; t != NULL; t = t->next)
    printf("%s ", t->surname);
  printf("\n");
  visitRbyCat(fout, h->next, z);
}

void STlistByCat(FILE *fout, ST st) {
  int i;
  for (i=0; i < st->M; i++)
    if (st->heads[i] != NULL)
      visitRbyCat(fout, st->heads[i], st->z);
}
