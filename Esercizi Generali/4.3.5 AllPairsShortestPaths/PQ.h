#ifndef PQ_H_DEFINED
#define PQ_H_DEFINED

typedef struct pqueue *PQ;

PQ      PQinit(int);
int     PQempty(PQ);
void    PQinsert(PQ, int *, int);
int     PQextractMin(PQ, int *);
void    PQchange (PQ, int *, int);
void    PQdisplay(PQ, int);
void	PQfree(PQ);


#endif
