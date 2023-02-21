#ifndef PQ_H
#define PQ_H

#include "Item.h"

typedef struct pqueue *PQ;

PQ      PQinit();
int     PQempty(PQ pq);
void    PQinsert(PQ pq, Item val);
Item    PQextractMax(PQ pq);
void    PQstore(FILE* fout, PQ pq);
void    PQload(FILE* fin, PQ pq);
int     PQsize(PQ pq);
void 	PQfree(PQ pq);

#endif
