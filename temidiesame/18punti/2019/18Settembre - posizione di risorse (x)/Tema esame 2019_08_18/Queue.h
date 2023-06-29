#ifndef _QUEUE_INCLUDED
#define _QUEUE_INCLUDED

typedef struct queue *Q;

typedef struct {
  int r;
  int c;
  int id;
  int dist;
} Mossa;

//MOSSA
Mossa MOSSAcreate(int r, int c, int id, int dist);

//QUEUE
Q QUEUEinit(void);
int QUEUEempty(Q q);
void QUEUEput (Q q, Mossa m);
Mossa QUEUEget(Q q);
void QUEUEfree(Q q);

#endif

