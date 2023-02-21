#include <stdlib.h>
#include <stdio.h>
#include "Item.h"
#include "PQ.h"
#include "ST.h"

struct pqueue { int *heap; Item *vett; ST hash; int *qp; int heapsize; };

static int PARENT(int i);
static int LEFT(int i);
static int RIGHT(int i);
static void Swap(PQ pq, int n1, int n2);
static void Heapify(PQ pq, int i);

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
  pq->heap = malloc(maxN*sizeof(int));
  pq->vett = malloc(maxN*sizeof(Item));
  pq->hash = STinit(maxN);
  pq->qp = malloc(maxN*sizeof(int));
  for (i=0; i < maxN; i++){
    pq->heap[i] = -1;
    pq->qp[i] = -1;
  }
  pq->heapsize = 0;
  return pq;
}

void PQfree(PQ pq) {
  free(pq->qp);
  STfree(pq->hash);
  free(pq->vett);
  free(pq->heap);
  free(pq);
}

int PQempty(PQ pq){
  return pq->heapsize == 0;
}

int PQsize(PQ pq) {
  return pq->heapsize;
}
void PQinsert (PQ pq, Item item){
  int i, j;
  i = j = pq->heapsize++;
  pq->vett[j] = item;
  STinsert(pq->hash, item, j);

  while ( (i>=1) && (PRIOget(pq->vett[pq->heap[PARENT(i)]]) < PRIOget(item)) )  {
    pq->heap[i] = pq->heap[PARENT(i)];
    pq->qp[pq->heap[i]] = i;
    i = (i-1)/2;
  }
  pq->heap[i] = j;
  pq->qp[j] = i;
}

static void Swap(PQ pq, int n1, int n2){
  int temp;

  temp = pq->heap[n1];
  pq->heap[n1] = pq->heap[n2];
  pq->heap[n2] = temp;

  n1 = pq->heap[n1];
  n2 = pq->heap[n2];
  temp = pq->qp[n1];
  pq->qp[n1] = pq->qp[n2];
  pq->qp[n2] = temp;
}

static void Heapify(PQ pq, int i) {
  int l, r, largest;
  l = LEFT(i);
  r = RIGHT(i);
  if (l < pq->heapsize && (PRIOget(pq->vett[pq->heap[l]]) > PRIOget(pq->vett[pq->heap[i]])) )
    largest = l;
  else
    largest = i;
  if (r < pq->heapsize && (PRIOget(pq->vett[pq->heap[r]]) > PRIOget(pq->vett[pq->heap[largest]])) )
    largest = r;
  if (largest != i) {
    Swap(pq, i,largest);
	Heapify(pq, largest);
  }
}


Item PQextractMax(PQ pq) {
  Item item;
  Swap (pq, 0, pq->heapsize-1);
  item = pq->vett[pq->heap[pq->heapsize-1]];
  pq->heapsize--;
  Heapify(pq, 0);
  return item;
}


Item PQshowMax(PQ pq){
  return pq->vett[pq->heap[0]];
}

void PQdisplay(PQ pq, int maxN){
  int i;
  printf("Hash table\n");
  STdisplay(pq->hash);

  printf("PQ: heapsize %d\n", PQsize(pq));

  printf("PQ: indices\n");
  for (i = 0; i < maxN; i++)
    printf("%d  ", pq->heap[i]);
  printf("\n");

  printf("QP: reverse indices\n");
  for (i = 0; i < maxN; i++)
    printf("%d  ", pq->qp[i]);
  printf("\n");
}


void PQchange (PQ pq, Item item) {
  int i, pos, temp, j;
  i = STsearch(pq->hash, item, &j);
  STchangePrio(pq->hash, item, j);
  if (i == -1) {
    printf("Item not found!\n");
    return;
  }
  pos = pq->qp[i];
  temp = pq->heap[pos];
  pq->vett[i] = item;

  while ( (pos>=1) && (PRIOget(pq->vett[pq->heap[PARENT(pos)]]) < PRIOget(item)) ) {
    pq->heap[pos] = pq->heap[PARENT(pos)];
    pq->qp[pq->heap[pos]] = pos;
    pos = (pos-1)/2;
  }
  pq->heap[pos] = temp;
  pq->qp[temp] = pos;

  Heapify(pq, pos);
}
