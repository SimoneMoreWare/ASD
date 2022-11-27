#ifndef GRAPH_H
#define GRAPH_H

#include "ST.h"
#include "listadj.h"
#include <stdio.h>

typedef struct edge { int v; int w; int wt; } Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *);
void  GRAPHinsertE(Graph G, int id1, int id2, int wt);
void  GRAPHstore(Graph G, FILE *fout);
void  GRAPHedges(Graph G, Edge *a);
int EDGEreadfromfile(FILE *fin);
void check_sottografocompleto_matrix(Graph G);
Listaadj LISTload(Graph G);
void printsortvertex(Graph G);
#endif
