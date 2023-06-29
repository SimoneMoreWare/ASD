#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include "cammino.h"

typedef enum{VERO, FALSO}Boolean;

typedef struct grafo *Grafo;

Grafo GRAFOinit();
Grafo GRAFOload(FILE *f);
void GRAFOinsertE(Grafo g, int id1, int id2, int wt);
void GRAFOintersezioneEStampaSottocammini(Grafo g, char *nomeFile, FILE *f);
void GRAFOsolve(Grafo g, int k, int p, char *inizio, char *fine);
void GRAFOfree(Grafo g);

#endif // GRAFO_H_INCLUDED
