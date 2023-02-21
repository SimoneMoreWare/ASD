#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"


typedef struct node *link;
struct node { int index; int weight; link next; } ;
struct G { int **madj; link *ladj; int V; int E; } ;

static link NEW(int dst, int w, link next);
static Edge EDGEcreate(int v, int w, int wt);
static void  insertE(Graph g, Edge e);

static link NEW(int dst, int w, link next) {
  link x = malloc(sizeof *x);
  if (x == NULL) return NULL;
  x->index = dst;
  x->weight = w;
  x->next = next;
  return x;
}

Graph GRAPHinit(int V) {
  int i;
  Graph g = malloc(sizeof(*g));
  if (g == NULL)
    return NULL;
  g->V = V;
  g->E = 0;
  g->ladj = malloc(V*sizeof(link));
  if (g->ladj == NULL)
    return NULL;
  for (i=0; i<V; i++)
    g->ladj[i] = NULL;
  g->madj = NULL;
  return g;
}

void GRAPHfree(Graph g, int matgen) {
  int v;
  link tmp, t;
  for (v=0; v < g->V; v++)
    for (t=g->ladj[v]; t != NULL;) {
      tmp = t;
      t = t->next;
      free(tmp);
    }
  free(g->ladj);
  if (matgen)
    for (v=0; v<g->V; v++)
      free(g->madj[v]);
  free(g->madj);
  free(g);
}

static Edge EDGEcreate(int v, int w, int wt) {
  Edge e;
  e.v = v;
  e.w = w;
  e.wt = wt;
  return e;
}

static void  insertE(Graph g, Edge e) {
  int v = e.v, w = e.w, wt = e.wt;
  g->ladj[v] = NEW(w, wt, g->ladj[v]);
  g->ladj[w] = NEW(v, wt, g->ladj[w]);
  g->E++;
}

void GRAPHinsertE(Graph g, int id1, int id2, int wt) {
  insertE(g, EDGEcreate(id1, id2, wt));
}

int GRAPHlist2mat(Graph g) {
  int i, j;
  link iter;
  if (g->madj != NULL)
    return 0;
  if (g->ladj == NULL)
    return -1;
  g->madj = malloc(g->V * sizeof(int*));
  if (g->madj == NULL)
    return -1;

  for (i=0; i<g->V; i++) {
    g->madj[i] = malloc(g->V * sizeof(int));
    if (g->madj[i] == NULL)
      return -1;
    for (j=0; j<g->V; j++)
      g->madj[i][j] = 0;
    iter = g->ladj[i];
    while(iter != NULL) {
      g->madj[i][iter->index] = iter->weight;
      iter = iter->next;
    }
  }
  return 0;
}

void GRAPHadjacent(Graph g, int *adjacentN, int *adjacentW, int index, int flag) {
  int i=0, j;
  link iter;
  if (flag == 0) {
    if (g->ladj == NULL)
      return;
    iter = g->ladj[index];
    while (iter != NULL) {
      adjacentN[i] = iter->index;
      adjacentW[i] = iter->weight;
      iter = iter->next;
      i++;
    }
  } else {
    if (g->madj == NULL)
      return;
    for (j=0; j<g->V; j++)
      if (g->madj[index][j]!=0) {
        adjacentN[i] = j;
        adjacentW[i] = g->madj[index][j];
        i++;
      }
    }
  return;
}

int GRAPHnodeDegree(Graph g, int index, int flag) {
  int i, cnt;
  link iter;
  if (flag == 0) {
    if (g->ladj == NULL)
      return 0;
    cnt = 0;
    iter = g->ladj[index];
    while(iter != NULL) {
      cnt++;
      iter = iter->next;
    }
  } else {
      if (g->madj == NULL)
        return 0;
      cnt = 0;
      for (i=0; i<g->V; i++)
        if (g->madj[index][i])
          cnt++;
    }
  return cnt;
}

