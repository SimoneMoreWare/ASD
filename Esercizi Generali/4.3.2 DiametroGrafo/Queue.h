#ifndef _QUEUE_INCLUDED
#define _QUEUE_INCLUDED

#include "Graph.h"

typedef struct queue *Q;

Q       QUEUEinit(void);
int     QUEUEempty(Q q);
void    QUEUEput (Q q, Edge e);
Edge    QUEUEget(Q q);
void    QUEUEfree(Q q);

#endif

