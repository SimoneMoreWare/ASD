#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include "ST.h"
#include "archi.h"
#include "Queue.h"

typedef struct grafo *Grafo;

Grafo GRAFOinit();
Grafo GRAFOload(FILE *f);
void GRAFOinsertE(Grafo g, int id1, int id2);
void GRAFOdeleteE(Grafo g, int id1, int id2);
Boolean GRAFOisConnesso(Grafo g);
Boolean GRAFOcheckGrado(Grafo g, int m);
Boolean GRAFOcheckCamminiMinimi(Grafo g, int k);
void GRAFOleggiArchi(Grafo g, FILE *f);
Boolean GRAFOverifica(Grafo g, int k, int m);
Archi GRAFOgeneraArchi(Grafo g);
void GRAFOsolve(Grafo g, int m, int k);
void GRAFOdeleteArchi(Grafo g);
void GRAFOfree(Grafo g);

#endif // GRAFO_H_INCLUDED
