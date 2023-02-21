#ifndef GRAPH_H
#define GRAPH_H

#include "ST.h"

typedef struct edge { int v; int w; } Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph g);
int   GRAPHnumV(Graph g);
void  GRAPHinsertE(Graph G, int id1, int id2);
void  GRAPHremoveE(Graph G, int id1, int id2);
int   GRAPHlongestPathVW(Graph g, int v, int w, int *maxlen, int *path);
Graph GRAPHreverse(Graph g);
int   GRAPHscc(Graph g, ST tab, int flag);
void  GRAPHturn2SCC(Graph g, ST tab);

#endif

