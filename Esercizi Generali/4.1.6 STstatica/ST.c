#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ST.h"


struct symboltable {Item *a; int maxN;};

static int binarySearch(Item *a, int l, int r, Key k);
static void quicksort(Item *a, int n);
static void quicksort_r(Item *a, int l, int r);
static int partition(Item *a, int l, int r);

ST STinit(int maxN) {
  int i;
  ST st;
  st = malloc(sizeof(*st));
  if (st == NULL) {
    printf("Memory allocation error\n");
    return NULL;
  }
  st->a = calloc(maxN,sizeof(Item));
  if (st->a == NULL) {
    printf("Memory allocation error\n");
    free(st);
    return NULL;
  }
  st->maxN = maxN;
  for (i=0; i<maxN; i++)
    st->a[i] = ITEMsetNull();
  return st;
}

void STfree(ST st) {
  int i;
  for (i=0;i<st->maxN;i++)
    ITEMfree(st->a[i]);
  free(st->a);
  free(st);
}

ST STload(FILE *fin) {
  int n, i;
  ST st;

  fscanf(fin, "%d", &n);
  st = STinit(n);

  for (i=0; i<n; i++) {
    st->a[i] = ITEMscan(fin);
    if (st->a[i] == NULL) return NULL;
  }

  quicksort(st->a, st->maxN);
  return st;
}

static void quicksort(Item *a, int n) {
    quicksort_r(a, 0, n-1);
}

static void quicksort_r(Item *a, int l, int r) {
  int q;
  if (r <= l)
    return;
  q = partition(a, l, r);
  quicksort_r(a, l, q-1);
  quicksort_r(a, q+1, r);
}

static int partition(Item *a, int l, int r) {
  int i = l-1, j = r;
  Item x = a[r], tmp;
  for(;;) {
    while(ITEMcompare(a[++i], x) < 0);
    while(ITEMcompare(a[--j], x) > 0)
      if (j==l) break;
    if (i>=j)
      break;
    tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
  }
  tmp = a[i];
  a[i] = a[r];
  a[r] = tmp;
  return i;
}

int STsearch(ST st, Key k) {
  return binarySearch(st->a, 0, st->maxN-1, k);
}

static int binarySearch(Item *a, int l, int r, Key k) {
  int mid, cmp;

  if (r >= l) {
    mid = l + (r - l)/2;
    cmp = KEYcompare(KEYget(a[mid]), k);
    if (cmp == 0)
      return mid;
    if (cmp > 0)
      return binarySearch(a, l, mid-1, k);
    return binarySearch(a, mid+1, r, k);
  }
  return -1;
}
