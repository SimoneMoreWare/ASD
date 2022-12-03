#ifndef GRAPH_H
#define GRAPH_H

#include "ST.h"

typedef struct edge { int v; int w; int wt; } Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *fin);
void  GRAPHstore(Graph G, FILE *fin);
int   GRAPHgetIndex(Graph G, char *label);
void  GRAPHinsertE(Graph G, int id1, int id2, int wt);
void  GRAPHremoveE(Graph G, int id1, int id2);
void  GRAPHedges(Graph G, Edge *a);
void  GRAPHspBF(Graph G, int id);
void GRAPHdfs(Graph G, int id,int *flag_back);
void dfsR(Graph G,Edge e,int *time,int *pre,int *post,int *st,int **flag_back);
int GRAPHfvertexdim(Graph G);
int GRAPHprintedge(Graph G);
#endif
