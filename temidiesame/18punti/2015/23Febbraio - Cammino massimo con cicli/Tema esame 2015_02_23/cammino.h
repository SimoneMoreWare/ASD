#ifndef CAMMINO_H_INCLUDED
#define CAMMINO_H_INCLUDED
#include "ST.h"

typedef struct{
   int *vertici;
   int dim, maxD;
}Cammino;

Cammino CAMMINOread(ST table, FILE *f);
Cammino CAMMINOcrea(int max);
void CAMMINOinsert(Cammino *c, int v);
void CAMMINOelimina(Cammino *c);
int *CAMMINOintersezione(Cammino c1, Cammino c2, int *dim);
void CAMMINOstampaSottocammini(Cammino c, int *intersezione, int dim, ST table, FILE *f);
void CAMMINOstampa(Cammino c, ST table, FILE *f);
void CAMMINOclear(Cammino *c);

#endif // CAMMINO_H_INCLUDED
