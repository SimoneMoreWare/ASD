#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"
#include "ST.h"

struct symboltable { Item *a; int *ind; int M;};

static int full(ST st, int i);
static int hash(Name n, int M);
/* static int hashU(Name n, int M); */
static int STsizeSet(int maxN);

ST STinit(int maxN) {
  int i;
  ST st = malloc(sizeof(*st));
  st->M = STsizeSet(maxN);
  st->a = malloc(st->M * sizeof(Item) );
  st->ind = malloc(st->M * sizeof(int) );
  for (i = 0; i < st->M; i++) {
    st->a[i] = ITEMsetNull();
    st->ind[i] = -1;
  }
  return st;
}

void STfree(ST st) {
  free(st->a);
  free(st->ind);
  free(st);
}

static int STsizeSet(int maxN) {
  int primes[16] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53 };
  int i = 0;
  if (maxN < primes[15]) {
    for (i = 0; i<16; i++)
      if (2*maxN <= primes[i])
        return primes[i];
  }
  else
    printf("Too many entries!\n");
  return -1;
}

static int hash(Name n, int M) {
  int h = 0, base = 127;
  for ( ; *n != '\0'; n++)
    h = (base * h + *n) % M;
  return h;
}

/*
static int hashU(Name n, int M) {
  int h, a = 31415, b = 27183;
  for ( h = 0; *n != '\0'; n++, a = a*b % (M-1))
    h = (a*h + *n) % M;
  return h;
}
*/

static int full(ST st, int i) {
  if (st->ind[i] != -1)
    return 1;
  return 0;
}


void STinsert(ST st, Item val, int index) {
  int i;
  i = hash(NAMEget(&val), st->M);
  while (full(st, i))
    i = (i+1)%st->M;
  st->a[i] = val;
  st->ind[i] = index;
}

int STsearch(ST st, Item val, int *index) {
  int i = hash(NAMEget(&val), st->M);
  while (full(st, i))
    if (NAMEcmp(NAMEget(&val), NAMEget(&st->a[i])) == 0) {
      *index = i;
      return st->ind[i];
    }
    else
      i = (i+1)%st->M;
  *index = -1;
  return -1;
}

void STdisplay(ST st) {
  int i;
  for (i = 0; i < st->M; i++) {
    printf("st->a[%d] = ", i);
    ITEMstore(st->a[i]);
    printf("\n");
  }
}

void STchangePrio(ST st, Item val, int i){
  st->a[i] = val;
}
