#ifndef GRAPH_H
#define GRAPH_H

#include "UF.h"
#include "ST.h"

typedef struct edge { int v; int w; int wt; } Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *);
void  GRAPHinsertE(Graph G, int id1, int id2, int wt);
int   GRAPHgetIndex(Graph G, char *label);
void  GRAPHstore(Graph G, FILE *fout);
void  GRAPHedges(Graph G, Edge *a);
void  GRAPHmstK(Graph G);
void  GRAPHmstP(Graph G, int id);


#endif
