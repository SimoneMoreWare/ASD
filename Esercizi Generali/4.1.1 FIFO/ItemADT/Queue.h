#ifndef _QUEUE_INCLUDED
#define _QUEUE_INCLUDED

#include "Item.h"

typedef struct queue *Q;

Q QUEUEinit(int size);
void QUEUEfree(Q q);
int QUEUEput(Q q, Item d);
int QUEUEget(Q q, Item *d);
void QUEUEshow(FILE *fp, Q q);
Q QUEUEscan(FILE *fp, int size);
int QUEUEnum(Q q);
int QUEUEempty(Q q);
int QUEUEfull(Q q);

#endif
