#ifndef PQ_H
#define PQ_H

typedef struct pqueue *PQ;

PQ      PQinit(int maxN);
int     PQempty(PQ pq);
void    PQinsert(PQ pq, Tree t);
Tree    PQextractMin(PQ pq);
Tree    PQreadMin(PQ pq);
int     PQsize(PQ pq);
void    PQfree(PQ pq);

#endif
