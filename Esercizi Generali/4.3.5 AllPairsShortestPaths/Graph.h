#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "ST.h"

typedef struct edge { int v; int w; int wt; } Edge;
typedef struct G *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
void  GRAPHinsertE(Graph G, int id1, int id2, int wt);
int  *GRAPHssspD(Graph g, int s);
int **GRAPHapspFW(Graph g);
int   GRAPHgetNumV(Graph g);
int  *GRAPHdfs(Graph g, int *nCC, int *isAcyclic);
void  GRAPHdeleteV(Graph g, int *set, int k);
void  GRAPHreset(Graph g);
void  GRAPHconnect(Graph g, int *cc, int nCC, int *sum, Edge *best, int *eNum, int **dist, char **tab);
#endif



