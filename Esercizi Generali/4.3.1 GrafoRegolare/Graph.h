#ifndef GRAPH_H
#define GRAPH_H

#include "ST.h"

typedef struct edge { int v; int w; int wt; } Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *fin);
int   GRAPHsearchByKey(Graph G, char *label);
void  GRAPHinsertE(Graph G, int id1, int id2, int wt);
int   GRAPHregular(Graph G);
void  GRAPHlongestPath(Graph G, int src);

#endif
