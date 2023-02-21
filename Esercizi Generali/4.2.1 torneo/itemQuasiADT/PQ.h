#ifndef PQ_H_INCLUDED
#define PQ_H_INCLUDED

#include "Item.h"



typedef struct pqueue *PQ;



PQ      PQinit(int);

void    PQinsert(PQ, Item);

Item    PQextractMin(PQ);

int     PQsize(PQ);

void    PQstore(PQ, FILE *);

void    PQload(PQ *, FILE *);

void    PQremove(PQ pq, Id id);

void    PQfree(PQ pq);

#endif /* PQ_H_INCLUDED */
