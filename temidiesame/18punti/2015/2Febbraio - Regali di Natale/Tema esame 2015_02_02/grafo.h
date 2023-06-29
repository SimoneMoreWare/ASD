#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include "ST.h"

typedef struct grafo *Grafo;

Grafo GRAFOinit();
Grafo GRAFOload(FILE *f);
void GRAFOinsertE(Grafo g, int id1, int id2);
Boolean GRAFOleggiProposta(Grafo g, FILE *f);
Boolean GRAFOverifica(Grafo g, char *nomeFile);
void GRAFOeliminaRegali(Grafo g);
void GRAFOsolve(Grafo g);
void GRAFOfree(Grafo g);

#endif // GRAFO_H_INCLUDED
