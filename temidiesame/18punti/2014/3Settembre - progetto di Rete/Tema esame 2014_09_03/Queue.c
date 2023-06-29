#include <stdlib.h>
#include "Queue.h"

typedef struct Qnode *link;

struct Qnode{ int e; link next; };

struct queue { link head; link tail; int size; };

static link NEW(int e, link next);


static link NEW(int e, link next) {
  link x = malloc(sizeof *x) ;
  x->e = e; x->next = next;
  return x;
}

Q Qinit() {
  Q q = malloc(sizeof *q) ;
  q->head = NULL;
  return q;
}

void Qfree(Q q) {
  link t;
  for (t=q->head; t != NULL; t = t->next)
    free(t);
  free(q);
}


int Qempty(Q q) {
  return q->head == NULL;
}


void Qput (Q q, int e) {
  if (q->head == NULL) {
    q->tail = NEW(e, q->head) ;
    q->head = q->tail;
    return;
  }
  q->tail->next = NEW(e, q->tail->next) ;
  q->tail = q->tail->next;
}

int Qget(Q q) {
  int e = q->head->e;
  link t = q->head->next;
  free(q->head);
  q->head = t;
  q->size--;
  return e;
}

