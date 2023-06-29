#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "ST.h"

typedef enum{FALSO, VERO}Boolean;

typedef struct{
	int *stanze, nStanze;
	int ricchezzaTotale;
}Path;

typedef struct grafo *Graph;

//PATH
Path PATHcrea(int nStanze);
void PATHprint(Graph g, Path p, FILE *f);
void PATHclear(Path p);

//GRAPH
Graph GRAPHinit(int V);
Graph GRAPHload(FILE *fp);
Path GRAPHpathLoad(Graph g, FILE *fp);
void GRAPHinsertE(Graph g, int id1, int id2, int wt);
int GRAPHpathCheck(Graph g, Path *p, int M, int PF);
Path GRAPHpathBest(Graph g, int M, int PF);
Path GRAPHpathBestR(Graph g, int M, int PF, int vite, Path *sol, Path bestSol, int *visited, int pos);
void GRAPHfree(Graph g);







#endif // GRAPH_H_INCLUDED
