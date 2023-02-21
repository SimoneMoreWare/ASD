#include <stdlib.h>
#include "Item.h"
#include "PQ.h"

struct pqueue { Item *array; int heapsize; };

static int LEFT(int i);
static int RIGHT(int i);
static int PARENT(int i);
static void Swap(PQ pq, int n1, int n2);

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
  PQ pq;
  pq = malloc(sizeof(*pq));
  pq->array = (Item *)malloc(maxN*sizeof(Item));
  pq->heapsize = 0;
  return pq;
}

void PQfree(PQ pq){
  free(pq->array);
  free(pq);
}

int PQempty(PQ pq) {
  return pq->heapsize == 0;
}

int PQsize(PQ pq) {
  return pq->heapsize;
}

void PQinsert (PQ pq, Item val) {
  int i;
  i  = pq->heapsize++;
  while( (i>=1) && (KEYcmp(KEYget(pq->array[PARENT(i)]), KEYget(val)) == -1) ) {
    pq->array[i] = pq->array[PARENT(i)];
    i = (i-1)/2;
  }
  pq->array[i] = val;
}

static void Swap(PQ pq, int n1, int n2) {
  Item temp;

  temp  = pq->array[n1];
  pq->array[n1] = pq->array[n2];
  pq->array[n2] = temp;
}


void Heapify(PQ pq, int i) {
  int l, r, largest;
  l = LEFT(i);
  r = RIGHT(i);
  if ( (l < pq->heapsize) && (KEYcmp(KEYget(pq->array[l]), KEYget(pq->array[i])) == 1) )
    largest = l;
  else
    largest = i;
  if ( (r < pq->heapsize) && (KEYcmp(KEYget(pq->array[r]), KEYget(pq->array[largest])) == 1))
    largest = r;
  if (largest != i) {
    Swap(pq, i,largest);
	Heapify(pq, largest);
  }
}

Item PQextractMax(PQ pq) {
  Item val;
  Swap (pq, 0,pq->heapsize-1);
  val = pq->array[pq->heapsize-1];
  pq->heapsize--;
  Heapify(pq, 0);
  return val;
}

Item PQshowMax(PQ pq) {
  return pq->array[0];
}

void PQdisplay(PQ pq) {
  int i;
  for (i = 0; i < pq->heapsize; i++)
    ITEMstore(pq->array[i]);
}

void PQchange (PQ pq, int pos, Item val) {
  while( (pos>=1) && (KEYcmp(KEYget(pq->array[PARENT(pos)]), KEYget(val)) == -1)) {
    pq->array[pos] = pq->array[PARENT(pos)];
	pos = (pos-1)/2;
  }
  pq->array[pos] = val;
  Heapify(pq, pos);
  return;
}
