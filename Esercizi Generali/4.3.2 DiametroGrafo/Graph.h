 #ifndef GRAPH_H
#define GRAPH_H

#include "Queue.h"
#include "BST.h"

typedef struct edge { int v; int w; int wt; } Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *fin);
int   GRAPHnumV(Graph G);
void  GRAPHinsertE(Graph G, int id1, int id2, int wt);
int   GRAPHbfs(Graph G, int i);
Edge *GRAPHlongestPath(Graph G, int src, int *len, int *val);
char *GRAPHsearchByIndex(Graph G, int i);


#endif
