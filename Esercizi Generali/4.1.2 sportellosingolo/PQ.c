#include <stdlib.h>
#include <stdio.h>
#include "PQ.h"

typedef struct PQnode* link;

struct PQnode { Item item; link next; };

static link head;
static link tail;
static int count;

static link NEW (Item item, link next) {
  link x;

  x = (link) malloc(sizeof *x);
  if (x == NULL) return NULL;
  x->item = item;
  x->next = next;
  return x;
}

void PQinit() {
  head = tail = NULL;
  count = 0;
}

int PQempty() {
  return head == NULL;
}

int PQsize() {
  return count;
}

void PQinsert(Item item) {
  if (head == NULL) {
    head = NEW(item, NULL);
    if (head == NULL) return;
    tail = head;
    count = 1;
  } else {
    tail->next = NEW(item, NULL);
    if (tail->next == NULL) return;
    tail = tail->next;
    count++;
  }
}

Item PQextractMax() {
  link x, p, best, p_best;
  Item toBeReturned;

  if (PQempty())
    return ITEMsetNull();
  x = head;
  p = NULL;
  best = head;
  p_best = NULL;

  while(x != NULL) {
    if (ITEMgreater(x->item, best->item)) {
      best = x;
      p_best = p;
    }
    p = x;
    x = x->next;
  }

  count--;
  if (best == tail)
    tail = p_best;
  if (best == head) {
    head = head->next;
  } else {
    p_best->next = best->next;
  }
  toBeReturned = best->item;
  free(best);
  return toBeReturned;
}

void PQstore(FILE *fout) {
  link iter = head;

  if (fout == stdout)
    fprintf(fout, "Number of elements in Priority Queue: %d\n", PQsize());
  while(iter != NULL) {
    ITEMstore(fout, iter->item);
    iter = iter->next;
  }
}

void PQload(FILE* fin) {
  Item toBeAdded = ITEMsetNull();
  while(1) {
    toBeAdded = ITEMscan(fin);
    if (toBeAdded.prio == -1)
      break;
    PQinsert(toBeAdded);
  }
}

void PQfree() {
  link iter = head, toBeDeleted = NULL;

  if (PQempty())
    return;
  while (iter != NULL) {
	toBeDeleted = iter;
	iter = iter->next;
	free(toBeDeleted);
  }
  PQinit();
}
