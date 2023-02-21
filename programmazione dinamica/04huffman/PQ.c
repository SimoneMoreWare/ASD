#include <stdlib.h>
#include <stdio.h>
#include "Item.h"
#include "Tree.h"
#include "PQ.h"

struct pqueue { Tree *array; int maxN; int heapsize; };

static int LEFT(int i) {
  return i*2+1;
}

static int RIGHT(int i) {
  return i*2+2;
}

static int PARENT(int i) {
  return (i-1)/2;
}

PQ PQinit(int maxN){
  int i;
  PQ pq;
  pq = malloc(sizeof(*pq));
  pq->array = (Tree *)malloc(maxN*sizeof(Tree));
  for (i=0; i< maxN; i++)
    pq->array[i] = NULL;
  pq->heapsize = 0;
  pq->maxN = maxN;

  return pq;
}

void PQfree(PQ pq){
  int i;
  for (i=0; i < pq->maxN; i++)
    TREEfree(pq->array[i]);
  free(pq);
}

int PQempty(PQ pq) {
  return pq->heapsize == 0;
}

int PQsize(PQ pq) {
  return pq->heapsize;
}


void PQinsert (PQ pq, Tree t) {
  int i;
  i  = pq->heapsize++;
  while( (i>=1) && (ITEMgt(TREEgetRootItem(pq->array[PARENT(i)]), TREEgetRootItem(t)))) {
    pq->array[i] = pq->array[PARENT(i)];
    i = (i-1)/2;
  }
  pq->array[i] = t;
  return;
}

void Swap(PQ pq, int n1, int n2) {
  Tree temp;
  temp  = pq->array[n1];
  pq->array[n1] = pq->array[n2];
  pq->array[n2] = temp;
  return;
}


void Heapify(PQ pq, int i) {
  int l, r, largest;
  l = LEFT(i);
  r = RIGHT(i);
  if ( (l < pq->heapsize) && (ITEMlt(TREEgetRootItem(pq->array[l]), TREEgetRootItem(pq->array[i])) ))
    largest = l;
  else
    largest = i;
  if ( (r < pq->heapsize) && (ITEMlt(TREEgetRootItem(pq->array[r]), TREEgetRootItem(pq->array[largest]))))
    largest = r;
  if (largest != i) {
    Swap(pq, i,largest);
	Heapify(pq, largest);
  }
  return;
}

Tree PQextractMin(PQ pq) {
  Swap (pq, 0,pq->heapsize-1);
  pq->heapsize--;
  Heapify(pq, 0);
  return pq->array[pq->heapsize];
}
