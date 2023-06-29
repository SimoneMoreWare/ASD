#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

typedef struct QUEUEnode *link;

struct QUEUEnode{Mossa m; link next; };
struct queue { link head; link tail; int size; };

static link NEW(Mossa m, link next);
static void LINKfree(link l);


//MOSSA
Mossa MOSSAcreate(int r, int c, int id, int dist){
    Mossa m;
    m.r=r;
    m.c=c;
    m.id=id;
    m.dist=dist;
    return m;
}


//QUEUE
static link NEW(Mossa m, link next) {
  link x = malloc(sizeof *x) ;
  x->m = m;
  x->next = next;
  return x;
}

Q QUEUEinit() {
  Q q = malloc(sizeof *q) ;
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

void QUEUEput (Q q, Mossa m) {
  if (q->head == NULL) {
    q->tail = NEW(m, q->head) ;
    q->head = q->tail;
    q->size += 1;
    return;
  }
  q->tail->next = NEW(m, q->tail->next) ;
  q->tail = q->tail->next;
  q->size += 1;
}

Mossa QUEUEget(Q q){
  Mossa m = q->head->m;
  link t = q->head->next;
  free(q->head);
  q->head = t;
  q->size--;
  return m;
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
