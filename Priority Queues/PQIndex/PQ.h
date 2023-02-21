#ifndef PQ_H_DEFINED
#define PQ_H_DEFINED

typedef struct pqueue *PQ;

PQ      PQinit(int maxN);
void    PQfree(PQ pq);
int     PQempty(PQ pq);
int     PQsize(PQ pq);
void    PQinsert(PQ pq, Item val);
Item    PQshowMax(PQ pq);
Item    PQextractMax(PQ pq);
void    PQdisplay(PQ pq, int maxN);
void    PQchange(PQ pq, Item val);

#endif
