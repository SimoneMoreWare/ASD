#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef enum{VERO, FALSO}Boolean;

typedef struct grafo *Grafo;

Grafo GRAFOinit(int V);
Grafo GRAFOload(FILE*f);
void GRAFOinsertE(Grafo g, int id1, int id2);
Boolean GRAFOcheck(Grafo g, char *nomeFile);
void GRAFOsolve(Grafo g);
void GRAFOfree(Grafo g);

void GRAFOprint(Grafo g, FILE *f);

#endif // GRAFO_H_INCLUDED
