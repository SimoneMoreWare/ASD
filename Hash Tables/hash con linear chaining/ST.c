#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"
#include "ST.h"

typedef struct STnode* link;
struct STnode { Item item;  link next; } ;

struct symbtab { link *heads; int N; int M; link z; };

static link NEW( Item item, link next);
static int STsizeSet(int maxN, int r);
static int hash(Key v, int M);
/* static int hashU(Key v, int M); */


static link NEW( Item item, link next) {
  link x = malloc(sizeof *x);
  x->item = item;
  x->next = next;
  return x;
}

ST STinit(int maxN) {
  int i, r;
  ST st = malloc(sizeof(*st));
  if(st == NULL) {
    printf("Memory allocation error\n");
    return NULL;
  }
  printf("Enter desired average list length: ");
  scanf("%d", &r);
  st->N = 0;
  st->M = STsizeSet(maxN, r);
  st->heads = malloc(st->M*sizeof(link));
  st->z = NEW(ITEMsetNull(), NULL);
  for (i=0; i < st->M; i++)
    st->heads[i] = st->z;
  return st;
}

static int STsizeSet(int maxN, int r) {
  int primes[16] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53 };
  int i = 0, avlength;
  avlength = maxN /r;
  if (maxN < primes[15]) {
    for (i = 0; i<16; i++)
      if (avlength <= primes[i])
        return primes[i];
  }
  else
    printf("Too many entries!\n");
  return -1;
}

void STfree(ST st) {
  int i;
  link t, u;
  for(i=0; i<st->M; i++)
    for (t = st->heads[i]; t != st->z; t = u){
      u = t->next;
      free(t);
  }
  free(st->heads);
  free(st);
}

int STcount(ST st) {
  return st->N;
}

int STempty(ST st) {
  if (STcount(st) == 0)
    return 1;
  return 0;
}

static int hash(Key v, int M) {
  int h = 0, base = 127;
  for ( ; *v != '\0'; v++)
    h = (base * h + *v) % M;
  return h;
}

/*
static int hashU(Key v, int M) {
  int h, a = 31415, b = 27183;
  for ( h = 0; *v != '\0'; v++, a = a*b % (M-1))
    h = (a*h + *v) % M;
  return h;
}
*/

void STinsert (ST st, Item val) {
  int i;
  i = hash(KEYget(&val), st->M);
  st->heads[i] = NEW(val, st->heads[i]);
  st->N++;
}

Item searchR(link t, Key k, link z) {
  if (t == z)
    return ITEMsetNull();
  if ((KEYcmp(KEYget(&t->item), k))==0)
    return t->item;
  return
     searchR(t->next, k, z);
}

Item STsearch(ST st, Key k) {
  return searchR(st->heads[hash(k, st->M)], k, st->z);
}

link deleteR(link x, Key k) {
   link t;
   if ( x == NULL )
    return NULL;
  if ((KEYcmp(KEYget(&x->item), k))==0) {
    t = x->next;
    free(x);
    return t;
  }
  x->next = deleteR(x->next, k);
  return x;
}

void STdelete(ST st, Key k) {
  int i = hash(k, st->M);
  st->heads[i] = deleteR(st->heads[i], k);
  st->N--;
}

void visitR(link h, link z) {
  if (h == z)
    return;
  ITEMstore(h->item);
  visitR(h->next, z);
  }

void STdisplay(ST st)  {
  int i;
  for (i=0; i < st->M; i++) {
    printf("st[%d]: ", i);
    visitR(st->heads[i], st->z);
    printf("\n");
  }
}
