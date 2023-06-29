#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include "ST.h"

typedef enum {VERO, FALSO}Boolean;

typedef struct{
    int v, w;
    float wt;
}Edge;

typedef struct grafo *Grafo;

//EDGE
Edge EDGEcreate(int id1, int id2, float wt);
void EDGEinsert(Edge *e, int *dim, int *maxD, Edge a);

//GRAFO
Grafo GRAFOinit(int V);
Grafo GRAFOload(FILE *f);
void GRAFOinsertE(Grafo g, int id1, int id2, float wt);
void GRAFOdeleteE(Grafo g, int id1, int id2);
Edge *GRAFOreadProposta(Grafo g, char *nomeFile, int *nArchi);
Boolean GRAFOisConnesso(Grafo g);
int GRAFOgetDiametro(Grafo g);
Boolean GRAFOcheckProposta(Grafo g, Edge *proposta, int nArchi, int *diametro);
void GRAFOcheckProposte(Grafo g, char *nomeFile1, char *nomeFile2);
void GRAFOsolve(Grafo g);
void GRAFOfree(Grafo g);

#endif // GRAFO_H_INCLUDED
