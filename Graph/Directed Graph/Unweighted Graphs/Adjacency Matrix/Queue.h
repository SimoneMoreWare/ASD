#ifndef QUEUE_H
#define QUEUE_H

#include "Graph.h"

typedef struct queue *Q;

Q       Qinit();
void    Qfree(Q q);
int     Qempty(Q q);
void    Qput (Q q, Edge e);
Edge    Qget(Q q);


#endif
