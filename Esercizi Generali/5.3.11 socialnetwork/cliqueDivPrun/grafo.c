#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

#define DBG 0

struct G {
    int **madj;
    int n_vertici;
};

int GRAPHgetNV(graph g) {
  if (g != NULL) return g->n_vertici;
  return -1;
}

graph GRAPHinit(int nV) {
    int i;
    graph g = malloc(sizeof(*g));
    if (g == NULL) return NULL;
    g->n_vertici = nV;
    g->madj = calloc(nV, sizeof(int*));
    for(i=0;i<nV;i++) g->madj[i] = calloc(nV, sizeof(int));
    return g;
}

void GRAPHinsertE(graph g, int src, int dst, int w) {
    if(src < 0 || dst < 0) return;
    if (g->madj == NULL) return;
    g->madj[src][dst] = g->madj[dst][src] = w;
    return;
}

int GRAPHadiacenti(graph g, int x, int y) {
  if (g == NULL || g->madj == NULL) return 0;
  return g->madj[x][y] != 0;
}

int GRAPHgetPeso(graph g, int x, int y) {
  if (g == NULL || g->madj == NULL) return 0;
  return g->madj[x][y];
}

void GRAPHfree(graph g) {
  int i, nV = g->n_vertici;

  for(i=0;i<nV;i++) free(g->madj[i]);
  free(g->madj);
  free(g);  
}
