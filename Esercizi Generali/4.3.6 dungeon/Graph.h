#ifndef GRAPH_H
#define GRAPH_H
#include "ST.h"


typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *fin);
void  GRAPHpath(Graph G);

#endif
