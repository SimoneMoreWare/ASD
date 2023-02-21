#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ST.h"

#define MAXL 31

static int sizeSet(int maxN);
static int hash(char *str, int M);

typedef struct htItem_ {
  char key[MAXL];
  int index;
} htItem;

struct hashtable {
  htItem *items;
  int N, M;
};

ST STinit(int maxN) {
  ST ht;
  int i;
  ht = malloc(sizeof(*ht));
  if (ht==NULL)
    return NULL;
  ht->N = 0;
  ht->M = sizeSet(maxN);
  ht->items = calloc(ht->M, sizeof(htItem) );
  if (ht->items==NULL)
    return NULL;
  for (i = 0; i < ht->M; i++)
    ht->items[i].index = -1;
  return ht;
}

static int sizeSet(int maxN) {
  int primes[16]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};
  int i = 0;
  if (maxN < primes[15]) {
    for (i = 0; i<16; i++)
      if (maxN*2 <= primes[i])
        return primes[i];
  }
  return -1;
}

static int hash(char *str, int M) {
  int h = 0, base = 127;
  for ( ; *str != '\0'; str++)
    h = (base * h + *str) % M;
  return h;
}

void STinsert(ST ht, char *str, int index) {
  int i = hash(str, ht->M);
  while (ht->items[i].index != -1)
    i = (i+1) % ht->M;
  strcpy(ht->items[i].key, str);
  ht->items[i].index = index;
  ht->N++;
}

int STsearch(ST ht, char *key) {
  int i = hash(key, ht->M);
  while (ht->items[i].index != -1)
    if (strcmp(key, ht->items[i].key) == 0)
      return ht->items[i].index;
    else
      i = (i+1) % ht->M;
  return -1;
}

void STfree(ST ht) {
  if (ht == NULL)
    return;
  free(ht->items);
  free(ht);
}


