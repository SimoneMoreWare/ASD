#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include "ST.h"

typedef struct grafo *Grafo;

Grafo GRAFOinit();
Grafo GRAFOload(FILE *f);
void GRAFOinsertE(Grafo g, int id1, int id2, int wt);
void GRAFOcamminoPesoMax(Grafo g);
void GRAFOsottoGrafo(Grafo g);
void GRAFOfree(Grafo g);

#endif // GRAFO_H_INCLUDED
