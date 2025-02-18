#ifndef GRAPH_H
#define GRAPH_H
#include "TriPack.h"

typedef struct Graph_t *Graph;

int GRAPHfindEdge(Graph G, int v, int w);
int GRAPHvertex(Graph G);
Graph GRAPHfile(FILE* file);
int GRAPHcheckFile(FILE* file, Graph G);
void GRAPHfindMaxTripack(Graph G);
int checkTriPack(Graph G, TriPack TP);

#endif