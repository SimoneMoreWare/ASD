#include <stdlib.h>
#include <stdio.h>
#include "Item.h"
#include "PQ.h"

struct pqueue { int *A; int *qp; int heapsize; };

static void Swap(PQ pq, int n1, int n2);
static void Heapify(PQ pq, int *mindist, int i);
static int LEFT(int i);
static int RIGHT(int i);
static int PARENT(int i);

static int LEFT(int i) {
  return i*2+1;
}

static int RIGHT(int i) {
  return i*2+2;
}

static int PARENT(int i) {
  return (i-1)/2;
}

PQ PQinit(int maxN) {
  int i;
  PQ pq = malloc(sizeof(*pq));
  pq->A = malloc(maxN*sizeof(int));
  pq->qp = malloc(maxN*sizeof(int));
  for (i=0; i < maxN; i++)
    pq->qp[i] = -1;
  pq->heapsize = 0;
  return pq;
}

void PQfree(PQ pq) {
  free(pq->qp);
  free(pq->A);
  free(pq);
}

int PQempty(PQ pq) {
  return pq->heapsize == 0;
}

void PQinsert (PQ pq, int *mindist, int node){
  int i;
  i = pq->heapsize++;
  pq->qp[node] = i;
  while (i>=1 && (mindist[pq->A[PARENT(i)]] > mindist[node])) {
    pq->A[i] = pq->A[PARENT(i)];
    pq->qp[pq->A[i]] = i;
    i = (i-1)/2;
  }
  pq->A[i] = node;
  pq->qp[node] = i;
  return;
}

static void Swap(PQ pq, int n1, int n2){
  int temp;

  temp = pq->A[n1];
  pq->A[n1] = pq->A[n2];
  pq->A[n2] = temp;

  n1 = pq->A[n1];
  n2 = pq->A[n2];
  temp = pq->qp[n1];
  pq->qp[n1] = pq->qp[n2];
  pq->qp[n2] = temp;

  return;
}

static void Heapify(PQ pq, int *mindist, int i) {
  int l, r, smallest;
  l = LEFT(i);
  r = RIGHT(i);
  if (l < pq->heapsize && (mindist[pq->A[l]] < mindist[pq->A[i]]))
    smallest = l;
  else
    smallest = i;
  if (r < pq->heapsize && (mindist[pq->A[r]] < mindist[pq->A[smallest]]))
    smallest = r;
  if (smallest != i) {
    Swap(pq, i,smallest);
	Heapify(pq, mindist, smallest);
  }
  return;
}

int PQextractMin(PQ pq, int *mindist) {
  int k;
  Swap (pq, 0, pq->heapsize-1);
  k = pq->A[pq->heapsize-1];
  pq->heapsize--;
  Heapify(pq, mindist, 0);
  return k;
}

void PQchange (PQ pq, int *mindist, int k) {
  int pos = pq->qp[k];
  int temp = pq->A[pos];

  while (pos>=1 && (mindist[pq->A[PARENT(pos)]] > mindist[pq->A[pos]])) {
    pq->A[pos] = pq->A[PARENT(pos)];
    pq->qp[pq->A[pos]] = pos;
    pos = (pos-1)/2;
  }
  pq->A[pos] = temp;
  pq->qp[temp] = pos;

  Heapify(pq, mindist, pos);
  return;
}


