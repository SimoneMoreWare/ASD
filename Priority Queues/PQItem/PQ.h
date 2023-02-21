#ifndef PQ_H_DEFINED
#define PQ_H_DEFINED

typedef struct pqueue *PQ;

PQ      PQinit(int maxN);
void    PQfree(PQ pq);
int     PQempty(PQ pq);
void    PQinsert(PQ pq, Item val);
Item    PQextractMax(PQ pq);
Item    PQshowMax(PQ pq);
void    PQdisplay(PQ pq);
int     PQsize(PQ pq);
void    PQchange(PQ pq, int pos, Item val);


#endif
