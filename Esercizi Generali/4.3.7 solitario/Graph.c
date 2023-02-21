#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"

#define maxWT 1000
#define maxV 100


typedef struct node *link;

struct node { int v; int wt; int dist; link next; } ;
struct graph { int V; int E; link *ladj; } ;

static Edge EDGEcreate(int v, int w, int wt);
static link NEW(int v, int wt, link next);
static void insertE(Graph G, Edge e);

static Edge EDGEcreate(int v, int w, int wt) {
  Edge e;
  e.v = v;
  e.w = w;
  e.wt = wt;
  return e;
}

static link NEW(int v, int wt, link next) {
  link x = malloc(sizeof *x);
  if (x == NULL) return NULL;
  x->v = v;
  x->wt = wt;
  x->next = next;
  return x;
}

Graph GRAPHinit(int V) {
  int v;
  Graph G = malloc(sizeof *G);
  if (G == NULL) return NULL;
  G->V = V;
  G->E = 0;
  G->ladj = malloc( V  * sizeof(link));
  if (G->ladj == NULL) return NULL;
  for (v = 0; v < V; v++)
    G->ladj[v] = NULL;
  return G;
}


void GRAPHfree(Graph G) {
  int v;
  link t, next;
  for (v=0; v < G->V; v++)
    for (t=G->ladj[v]; t != NULL; t = next) {
      next = t->next;
      free(t);
    }
  free(G->ladj);
  free(G);
}


void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
  insertE(G, EDGEcreate(id1, id2, wt));
}

static void  insertE(Graph G, Edge e) {
  int v = e.v, w = e.w, wt = e.wt;
  if (v == w)
    return;
  G->ladj[v] = NEW(w, wt, G->ladj[v]);
  G->E++;
}

int GRAPHedges(Edge *a, Graph G) {
  int v, E = 0;
  link t;
  for (v=0; v < G->V; v++)
    for (t=G->ladj[v]; t != NULL; t = t->next)
      a[E++] = EDGEcreate(v, t->v, t->wt);
  return E;
}

