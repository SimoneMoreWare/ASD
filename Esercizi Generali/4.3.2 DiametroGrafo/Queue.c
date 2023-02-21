#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

typedef struct QUEUEnode *link;

struct QUEUEnode{ Edge e; link next; };
struct queue { link head; link tail; int size; };

static link NEW(Edge E, link next);
static void LINKfree(link l);

static link NEW(Edge E, link next) {
  link x = malloc(sizeof *x) ;
  if (x == NULL) return NULL;
  x->e = E; x->next = next;
  return x;
}

Q QUEUEinit() {
  Q q = malloc(sizeof *q) ;
  if (q == NULL) return NULL;
  q->head = NULL;
  q->size = 0;
  return q;
}

int QUEUEempty(Q q) {
  return q->head == NULL;
}

int QUEUEsize(Q q) {
    return q->size;
}

void QUEUEput (Q q, Edge e) {
  if (q->head == NULL) {
    q->tail = NEW(e, q->head) ;
    if (q->tail == NULL) exit(-1);
    q->head = q->tail;
    q->size += 1;
    return;
  }
  q->tail->next = NEW(e, q->tail->next);
  if (q->tail->next == NULL) exit(-1);
  q->tail = q->tail->next;
  q->size += 1;
}

Edge QUEUEget(Q q){
  Edge e = q->head->e;
  link t = q->head->next;
  free(q->head);
  q->head = t;
  q->size--;
  return e;
}

static void LINKfree(link l) {
  if (l != NULL) {
    LINKfree(l->next);
    free(l);
  }
}

void QUEUEfree(Q q) {
  LINKfree(q->head);
  free(q);
}
