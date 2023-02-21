#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"
#include "ST.h"

struct symboltable { Item *a; int N; int M;};

static int STsizeSet(int maxN);
static int full(ST st, int i);
static int hash1(Key k, int M);
static int hash2(Key k);

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

static int hash1(Key k, int M) {
  int h = 0, base = 127;
  for ( ; *k != '\0'; k++)
    h = (base * h + *k) % M;
  return h;
}

static int hash2(Key k) {
  int h = 0, base = 127;
  for ( ; *k != '\0'; k++)
    h = (base * h + *k);
  h = ((h % 97) + 1);
  return h;
}

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
  int i = hash1(KEYget(&item), st->M);
  int j = hash2(KEYget(&item));
  while (full(st, i))
    i = (i+j)%st->M;
  st->a[i] = item;
  st->N++;
}

Item STsearch(ST st, Key k) {
  int i = hash1(k, st->M);
  int j = hash2(k);
    while (full(st, i))
      if (KEYcmp(k, KEYget(&st->a[i]))==0)
        return st->a[i];
      else
        i = (i+j)%st->M;
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
  int i = hash1(k, st->M), j = hash2(k), t;
  Item tmp;
  while (full(st, i))
    if (KEYcmp(k, KEYget(&st->a[i]))==0)
      break;
    else
      i = (i+j) % st->M;
  if (ITEMcheckNull(st->a[i]))
    return;
  st->a[i] = ITEMsetNull();
  st->N--;
  for (t = i+1; full(st, t); t = (t+1)%st->M, st->N--) {
    tmp = st->a[t];
    st->a[t] = ITEMsetNull();
    STinsert(st, tmp);
  }
}
