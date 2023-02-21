#ifndef GRAPH_H
#define GRAPH_H

typedef struct { int v; int w; int wt;} Edge;
Edge EDGE(int v, int w, int wt);

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
void  GRAPHinsertE(Graph G, int id1, int id2, int wt);
int   GRAPHedges(Edge *a, Graph G);

#endif


