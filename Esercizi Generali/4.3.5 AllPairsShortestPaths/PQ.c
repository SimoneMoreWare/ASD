#include <stdlib.h>
#include <stdio.h>
#include "PQ.h"
#define LEFT(i)   	((i*2) + 1)
#define RIGHT(i)	((i*2) + 2)
#define PARENT(i)	((i-1) / 2)

struct pqueue { int *A; int *qp; int heapsize; };

PQ PQinit(int maxN) {
  int i;
  PQ pq = malloc(sizeof(*pq));
  if (pq == NULL) return NULL;
  pq->A = malloc(maxN*sizeof(int));
  if (pq->A == NULL) return NULL;
  pq->qp = malloc(maxN*sizeof(int));
  if (pq->qp == NULL) return NULL;
  for (i=0; i < maxN; i++)
    pq->qp[i] = -1;
  pq->heapsize = 0;
  return pq;
}

void PQfree(PQ pq) {
  free(pq->A);
  free(pq->qp);
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

void Swap(PQ pq, int n1, int n2){
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

  void PQdisplay(PQ pq, int maxN){
  int i;
  printf("priority queue\n");
  for (i = 0; i < pq->heapsize; i++) {
    printf("pq->A[%d] = %d\n", i, pq->A[i]);
  }
  printf("PQ: indices\n");
  for (i = 0; i < pq->heapsize; i++)
    printf("%d  ", pq->A[i]);
  printf("\n");
  printf("QP: reverse indices\n");
  for (i = 0; i < maxN; i++)
    printf("%d  ", pq->qp[i]);
  printf("\n");
}

void Heapify(PQ pq, int *mindist, int i) {
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

