#include <stdlib.h>
#include <stdio.h>
#include "PQ.h"

typedef struct PQnode* link;

struct PQnode { Item item; link next; };
struct pqueue { link head; link tail; int count; };

static link NEW (Item item, link next) {
  link x;
  x = (link) malloc(sizeof *x);
  if (x == NULL) return NULL;
  x->item = item;
  x->next = next;
  return x;
}

PQ PQinit() {
  PQ pq;
  pq = malloc(sizeof(*pq));
  if (pq == NULL) return NULL;
  pq->head = pq->tail = NULL;
  pq->count = 0;
  return pq;
}

int PQempty(PQ pq) {
  if (pq == NULL)
    return 1;
  return pq->head == NULL;
}

int PQsize(PQ pq) {
  return pq->count;
}

void PQinsert(PQ pq, Item val) {
  if (pq->head == NULL) {
    pq->head = NEW(val, NULL);
    if (pq->head == NULL) return;
    pq->tail = pq->head;
    pq->count = 1;
  } else {
    pq->tail->next = NEW(val, NULL);
    if (pq->tail->next == NULL) return;
    pq->tail = pq->tail->next;
    pq->count++;
  }
}

Item PQextractMax(PQ pq) {
  link x, p, best, p_best;
  Item toBeReturned;

  if (PQempty(pq))
    return ITEMsetNull();

  x = pq->head;
  p = NULL;
  best = pq->head;
  p_best = NULL;

  while(x != NULL) {
    if (ITEMgreater(x->item, best->item)) {
      best = x;
      p_best = p;
    }
    p = x;
    x = x->next;
  }

  pq->count--;
  if (best == pq->tail)
    pq->tail = p_best;
  if (best == pq->head) {
    pq->head = pq->head->next;
  } else {
    p_best->next = best->next;
  }
  toBeReturned = best->item;
  free(best);

  return toBeReturned;
}

void PQstore(FILE *fout, PQ pq) {
  link iter;
  if (fout == stdout)
    fprintf(fout, "Number of elements in queue: %d\n", PQsize(pq));
  iter = pq->head;
  while(iter != NULL) {
    ITEMstore(fout, iter->item);
    iter = iter->next;
  }
}

void PQload(FILE* in, PQ pq) {
  Item toBeAdded = ITEMsetNull();
  while(1) {
    toBeAdded = ITEMscan(in);
    if (toBeAdded.prio == -1)
      break;
    PQinsert(pq, toBeAdded);
  }
}

void PQfree(PQ pq) {
  link iter = pq->head, toBeDeleted = NULL;

  if (pq == NULL)
    return;
  while (iter != NULL) {
	toBeDeleted = iter;
	iter = iter->next;
	free(toBeDeleted);
  }
  free (pq);
}
