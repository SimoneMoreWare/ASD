#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include "ST.h"

typedef struct{
    int v, w;
}Edge;

typedef struct grafo *Graph;

typedef enum{VERO, FALSO}Boolean;

typedef enum{DIVERSO, UGUALE}Simboli;

//Edge
Edge EDGEcreate(int v, int w);
Simboli EDGEcompare(Edge e1, Edge e2);

//Grafo
Graph GRAPHinit(int V);
Graph GRAPHload(FILE *f);
void GRAPHinsertE(Graph g, int id1, int id2);
void GRAPHaddEliminati(Graph g, Vertice v);
Boolean GRAPHisEliminato(Graph g, Vertice v);
Boolean GRAPHkCore(Graph g, int k);
void GRAPHverticiKCorePrint(Graph g, FILE *f);
Edge *GRAPHedges(Graph g);
Boolean GRAPHarcoExist(Edge *archi, Edge e, int dim);
Boolean GRAPHisConnesso(Graph g);
void GRAPHjConnected(Graph g, int j);



#endif // GRAFO_H_INCLUDED
