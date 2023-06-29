//
//  GRAPH.h
//  Pluto
//
//  Created by Alessio Corona on 18/02/23.
//

#ifndef GRAPH_h
#define GRAPH_h

#include "SymbolTable.h"
#include <stdio.h>

typedef struct grafo_t *GRAPH;

typedef struct {
    int v1, v2;
}Edge;

typedef enum {VERO, FALSO} boolean;

typedef struct {
    int *kernel;
    int size;
} kernel;


GRAPH GRAPHinit(void);
GRAPH GRAPHload(char *nomefile, int *nv);
boolean IsKernel(char *nomefile, GRAPH G);
kernel powerset(GRAPH G);
boolean IsValid(GRAPH G, int *kernel, int dim);
boolean isVertexKernel(int v, kernel k);
void GRAPHpath(GRAPH g, kernel k);
void GRAPHfree(GRAPH g);

#endif /* GRAPH_h */
