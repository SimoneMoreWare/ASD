#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"
#include "ST.h"

struct symboltable { Item *a; int N; int M;};

static int full(ST st, int i);
static int hash(Key k, int M);
/* static int hashU(Key k, int M); */
static int STsizeSet(int maxN);

ST STinit(int maxN) {
  int i;
  ST st = malloc(sizeof(*st));
  st->N = 0;
  st->M = STsizeSet(maxN);
  st->a = malloc(st->M * sizeof(Item) );
  for (i = 0; i < st->M; i++)
    st->a[i] = ITEMsetNull();
  return st;
}

void STfree(ST st) {
  free(st->a);
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

static int hash(Key k, int M) {
  int h = 0, base = 127;
  for ( ; *k != '\0'; k++)
    h = (base * h + *k) % M;
  return h;
}

/*
static int hashU(Key k, int M) {
  int h, a = 31415, b = 27183;
  for ( h = 0; *k != '\0'; k++, a = a*b % (M-1))
    h = (a*h + *k) % M;
  return h;
}
*/

int STcount(ST st) {
  return st->N;
}

int STempty(ST st) {
  if (STcount(st) == 0)
    return 1;
  return 0;
}

static int full(ST st, int i) {
  if (ITEMcheckNull(st->a[i]))
    return 0;
  return 1;
}

void STinsert(ST st, Item item) {
  int i = hash(KEYget(&item), st->M);
  while (full(st, i))
    i = (i+1)%st->M;
  st->a[i] = item;
  st->N++;
}

Item STsearch(ST st, Key k) {
  int i = hash(k, st->M);
  while (full(st, i))
    if (KEYcmp(k, KEYget(&st->a[i]))==0)
      return st->a[i];
    else
      i = (i+1)%st->M;
  return ITEMsetNull();
}

void STdisplay(ST st) {
  int i;
  for (i = 0; i < st->M; i++) {
    printf("st->a[%d] = ", i);
    ITEMstore(st->a[i]);
    printf("\n");
  }
}

void STdelete(ST st, Key k) {
  int j, i = hash(k, st->M);
  Item tmp;
  while (full(st, i))
    if (KEYcmp(k, KEYget(&st->a[i]))==0)
      break;
    else
      i = (i+1) % st->M;
  if (ITEMcheckNull(st->a[i]))
    return;
  st->a[i] = ITEMsetNull();
  st->N--;
  for (j = i+1; full(st, j); j = (j+1)%st->M, st->N--) {
    tmp = st->a[j];
    st->a[j] = ITEMsetNull();
    STinsert(st, tmp);
  }
}
