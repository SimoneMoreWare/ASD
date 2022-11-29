#ifndef DAG_H
#define DAG_H

#include "ST.h"

typedef struct edge { int v; int w; } Edge;

typedef struct dag *Dag;

Dag   DAGinit(int V);
void  DAGfree(Dag D);
Dag   DAGload(FILE *fin);
void  DAGstore(Dag D, FILE *fout);
int   DAGgetIndex(Dag D, char *label);
void  DAGinsertE(Dag D, int id1, int id2);
void  DAGremoveE(Dag D, int id1, int id2);
void  DAGts(Dag D);
void  DAGedges(Dag D, Edge *a);
#endif

