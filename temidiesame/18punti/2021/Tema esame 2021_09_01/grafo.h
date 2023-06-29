#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include "cicli.h"

typedef struct grafo *Graph;

Graph GRAPHinit(int V);
Graph GRAPHload(FILE *f);
void GRAPHreadCicli(Graph g, FILE *f);
void GRAPHfree(Graph g);
Boolean GRAPHverifica(Graph g, FILE *f);
void GRAPHsolve(Graph g);
void GRAPHinsertEdge(Graph g, int v, int w);



#endif // GRAFO_H_INCLUDED
