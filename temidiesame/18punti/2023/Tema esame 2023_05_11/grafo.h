#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include "trianglePacking.h"

typedef struct grafo *Grafo;

Grafo GRAFOinit(int V);
Grafo GRAFOload(FILE *f);
void GRAFOinsertE(Grafo g, int id1, int id2);
Boolean GRAFOverifica(Grafo g, char *nomeFile);
void GRAFOsolve(Grafo g);
void GRAFOfree(Grafo g);

#endif // GRAFO_H_INCLUDED
