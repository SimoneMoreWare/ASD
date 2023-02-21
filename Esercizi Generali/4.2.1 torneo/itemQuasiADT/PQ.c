#include <stdlib.h>

#include <string.h>

#include <stdio.h>

#include "Item.h"

#include "PQ.h"



struct pqueue { Item *array; int heapsize; int maxEl; };



static int  LEFT(int i);

static int  RIGHT(int i);

static int  PARENT(int i);

static void Swap(PQ pq, int n1, int n2);

static void HEAPify(PQ pq, int i);



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

  if (pq == NULL) return NULL;

  pq->array = (Item *)malloc(maxN*sizeof(Item));

  if (pq->array == NULL) return NULL;

  pq->heapsize = 0;

  pq->maxEl = maxN;

  return pq;

}



int PQsize(PQ pq) {

  return pq->heapsize;

}



void PQinsert (PQ pq, Item item) {

  int i;

  if (pq->heapsize == pq->maxEl) {

    pq->maxEl *= 2;

    pq->array = realloc(pq->array, pq->maxEl * sizeof(Item));

    if (pq->array == NULL) exit(-1);

  }

  i  = pq->heapsize++;

  while( (i>=1) && (ITEMgreater(pq->array[PARENT(i)], item)) ) {

    pq->array[i] = pq->array[PARENT(i)];

    i = (i-1)/2;

  }

  pq->array[i] = item;

  return;

}



static void Swap(PQ pq, int n1, int n2) {

  Item temp;



  temp  = pq->array[n1];

  pq->array[n1] = pq->array[n2];

  pq->array[n2] = temp;

  return;

}



static void HEAPify(PQ pq, int i) {

  int l, r, smallest;

  l = LEFT(i);

  r = RIGHT(i);

  if ( (l < pq->heapsize) && (ITEMless(pq->array[l], pq->array[i])) )

    smallest = l;

  else

    smallest = i;

  if ( (r < pq->heapsize) && (ITEMless(pq->array[r], pq->array[smallest])))

    smallest = r;

  if (smallest != i) {

    Swap(pq, i,smallest);

	HEAPify(pq, smallest);

  }

  return;

}



Item PQextractMin(PQ pq) {

  Item item;

  Swap (pq, 0,pq->heapsize-1);

  item = pq->array[pq->heapsize-1];

  pq->heapsize--;

  HEAPify(pq, 0);

  return item;

}



void PQstore(PQ pq, FILE *fp){

  int i;

  if (pq == NULL)

    return;

  for(i=0;i<pq->heapsize;i++)

    ITEMstore(fp, pq->array[i]);

}



void PQremove(PQ pq, Id id) {

  int i, found=0;

  Id k;

  for(i=0;i<pq->heapsize && !found;i++) {

    GETid(pq->array[i], k);

    if (IDcompare(k, id)==0) {

      found = 1;

      Swap(pq, i, pq->heapsize-1);

      pq->heapsize--;

      HEAPify(pq, i);

    }

  }

}



void PQload(PQ *pq, FILE *fp){

  int i, cnt;



  fscanf(fp, "%d", &cnt);

  if (*pq == NULL) {

    *pq = PQinit(1);

    if (*pq == NULL) return;

  }

  for(i=0;i<cnt;i++)

    PQinsert(*pq, ITEMscan(fp));

}



void PQfree(PQ pq) {

  if (pq == NULL)

    return;

  free (pq->array);

  free (pq);

}
