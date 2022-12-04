#ifndef GRAPH_H
#define GRAPH_H

#include "ST.h"

typedef struct edge { int v; int w; int wt; } Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *fin);
void  GRAPHstore(Graph G, FILE *fin);
void  GRAPHinsertE(Graph G, int id1, int id2, int wt);
void  GRAPHremoveE(Graph G, int id1, int id2);
void  GRAPHedges(Graph G, Edge *a);
void GRAPHdfs(Graph G, int id,int *flag_back, Edge **dagedges,int *cnt,int *countedgeback);
void dfsR(Graph G,Edge e,int *time,int *pre,int *post,int *st,int **flag_back,Edge ***dagedges,int **cnt,int **countedgeback);
void EDGEdag(Graph G,Edge *dagedges,int cnt,int countedgeback);
int GRAPHfvertexdim(Graph G);
void TSdfsR(Graph D, int v, int *ts, int *pre, int *time);
void DAGrts(Graph D);
void DAGlongestpath(Graph D,int *ts,int id,int i);
#endif
