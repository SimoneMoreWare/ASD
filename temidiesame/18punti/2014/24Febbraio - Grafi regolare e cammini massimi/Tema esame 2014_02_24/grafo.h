#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include "ST.h"

typedef enum{VERO, FALSO}Boolean;

typedef struct grafo *Grafo;

Grafo GRAPHinit();
Grafo GRAPHload(FILE *f);
Boolean GRAPHisRegular(Grafo g);
void GRAPHcamminoMassimo(Grafo g, char *sorgente);
void GRAPHinsertE(Grafo g, int id1, int id2, int wt);
void GRAPHfree(Grafo g);

#endif // GRAFO_H_INCLUDED
