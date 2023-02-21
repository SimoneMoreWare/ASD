#ifndef PQ_H_DEFINED
#define PQ_H_DEFINED
#include "Item.h"

typedef struct pqueue *PQ;

PQ      PQinit(int);
void    PQfree(PQ pq);
void    PQinsert(PQ, Item);
Item    PQextractMin(PQ);
int     PQsize(PQ);
void    PQstore(PQ, FILE *);
void    PQload(PQ *, FILE *);
void    PQremove(PQ pq, Id id);
#endif
