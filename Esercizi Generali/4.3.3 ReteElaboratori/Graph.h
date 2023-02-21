#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#define MAXL 31

typedef struct edge { int v; int w; int wt; } Edge;
typedef struct { char name[MAXL]; char subnet[MAXL]; } Vertex;

typedef struct G* Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph g, int matgen);
void  GRAPHinsertE(Graph g, int id1, int id2, int wt);
int   GRAPHlist2mat(Graph g);
void  GRAPHadjacent(Graph g, int *adjacentN, int *adjacentW, int index, int flag);
int   GRAPHnodeDegree(Graph g, int index, int flag);
#endif

