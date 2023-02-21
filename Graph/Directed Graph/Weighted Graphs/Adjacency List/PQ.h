#ifndef PQ_H_DEFINED
#define PQ_H_DEFINED

typedef struct pqueue *PQ;

PQ      PQinit(int maxN);
void    PQfree(PQ pq);
int     PQempty(PQ pq);
void    PQinsert(PQ pq, int *mindist, int node);
int     PQextractMin(PQ pq, int *mindist);
void    PQchange (PQ pq, int *mindist, int k);

#endif
