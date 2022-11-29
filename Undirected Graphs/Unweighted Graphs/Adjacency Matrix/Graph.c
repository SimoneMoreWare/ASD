#include <stdlib.h>
#include <stdio.h>
#include "ST.h"
#include "Queue.h"
#include "Graph.h"

#define MAXC 11

struct graph {int V; int E; int **madj; ST tab; };
static Edge  EDGEcreate(int v, int w);
static int **MATRIXint(int r, int c, int val);
static void  insertE(Graph G, Edge e);
static void  removeE(Graph G, Edge e);
static int   pathR(Graph G, int v, int w, int *visited);
static int   pathRH(Graph G, int v, int w, int d, int *visited);
static void  bfs(Graph G, Edge e, int *time, int *pre, int *st);

static Edge EDGEcreate(int v, int w) {
  Edge e;
  e.v = v;
  e.w = w;
  return e;
}

static int **MATRIXint(int r, int c, int val) {
  int i, j;
  int **t = malloc(r * sizeof(int *));
  if (t==NULL)
    return NULL;

  for (i=0; i < r; i++) {
    t[i] = malloc(c * sizeof(int));
    if (t[i]==NULL)
      return NULL;
  }
  for (i=0; i < r; i++)
    for (j=0; j < c; j++)
      t[i][j] = val;
  return t;
}

Graph GRAPHinit(int V) {
  Graph G = malloc(sizeof *G);
  if (G == NULL)
    return NULL;
  G->V = V;
  G->E = 0;
  G->madj = MATRIXint(V, V, 0);
  if (G->madj == NULL)
    return NULL;
  G->tab = STinit(V);
  if (G->tab == NULL)
    return NULL;
  return G;
}

void GRAPHfree(Graph G) {
  int i;
  for (i=0; i<G->V; i++)
    free(G->madj[i]);
  free(G->madj);
  STfree(G->tab);
  free(G);
}

Graph GRAPHload(FILE *fin) {
  int V, i, id1, id2;
  char label1[MAXC], label2[MAXC];
  Graph G;

  fscanf(fin, "%d", &V);
  G = GRAPHinit(V);

  for (i=0; i<V; i++) {
    fscanf(fin, "%s", label1);
    STinsert(G->tab, label1, i);
  }

  while(fscanf(fin, "%s %s", label1, label2) == 2) {
    id1 = STsearch(G->tab, label1);
    id2 = STsearch(G->tab, label2);
    if (id1 >= 0 && id2 >=0)
      GRAPHinsertE(G, id1, id2);
  }
  return G;
}

static void  insertE(Graph G, Edge e) {
  int v = e.v, w = e.w;

  if (G->madj[v][w] == 0)
    G->E++;
  G->madj[v][w] = 1;
  G->madj[w][v] = 1;
}

void GRAPHstore(Graph G, FILE *fout) {
  int i;
  Edge *a;

  a = malloc(G->E * sizeof(Edge));
  if (a == NULL)
    return;

  GRAPHedges(G, a);

  fprintf(fout, "%d\n", G->V);
  for (i = 0; i < G->V; i++)
    fprintf(fout, "%s\n", STsearchByIndex(G->tab, i));

  for (i = 0; i < G->E; i++)
    fprintf(fout, "%s  %s\n", STsearchByIndex(G->tab, a[i].v), STsearchByIndex(G->tab, a[i].w));

}

int GRAPHgetIndex(Graph G, char *label) {
  int id;
  id = STsearch(G->tab, label);
  if (id == -1) {
    id = STsize(G->tab);
    STinsert(G->tab, label, id);
  }
  return id;
}

void GRAPHinsertE(Graph G, int id1, int id2) {
  insertE(G, EDGEcreate(id1, id2));
}

void GRAPHremoveE(Graph G, int id1, int id2) {
  removeE(G, EDGEcreate(id1, id2));
}

static void  removeE(Graph G, Edge e) {
  int v = e.v, w = e.w;
  if (G->madj[v][w] == 1)
    G->E--;
  G->madj[v][w] = 0;
  G->madj[w][v] = 0;
}

void  GRAPHedges(Graph G, Edge *a) {
  int v, w, E = 0;
  for (v=0; v < G->V; v++)
    for (w=v+1; w < G->V; w++)
      if (G->madj[v][w] == 1)
        a[E++] = EDGEcreate(v, w);
}

void GRAPHpath(Graph G, int id1, int id2) {
  int t, found, *visited;

  visited = malloc(G->V*sizeof(int));
  if (visited == NULL)
    return;
  for ( t = 0 ; t < G->V ; t++)
    visited[t] = 0;

  if (id1 < 0 || id2 < 0)
    return;

  found = pathR(G, id1, id2, visited);
  if (found == 0)
    printf("\n Path not found!\n");
}

static int pathR(Graph G, int v, int w, int *visited) {
  int t;
  if (v == w)
    return 1;
  visited[v] = 1;
  for ( t = 0 ; t < G->V ; t++)
    if (G->madj[v][t] == 1)
      if (visited[t] == 0)
        if (pathR(G, t, w, visited)) {
          printf("edge (%s, %s) belongs to path \n", STsearchByIndex(G->tab, v), STsearchByIndex(G->tab, t));
          return 1;
        }
  return 0;
}

void GRAPHpathH(Graph G, int id1, int id2) {
  int t, found, *visited;

  visited = malloc(G->V*sizeof(int));
  if (visited == NULL)
    return;
  for ( t = 0 ; t < G->V ; t++)
    visited[t] = 0;

  if (id1 < 0 || id2 < 0)
      return;

  found = pathRH(G, id1, id2, G->V-1, visited);
  if (found == 0)
    printf("\n Hamiltonian path not found!\n");
}

int pathRH(Graph G, int v, int w, int d, int *visited) {
  int t;
  if (v == w) {
    if (d == 0)
      return 1;
    else
      return 0;
  }
  visited[v] = 1;
  for ( t = 0 ; t < G->V ; t++)
  if (G->madj[v][t] == 1)
    if (visited[t] == 0)
      if (pathRH(G, t, w, d-1, visited)) {
        printf("edge (%s, %s) belongs to path \n", STsearchByIndex(G->tab, v), STsearchByIndex(G->tab, t));
        return 1;
      }
  visited[v] = 0;
  return 0;
}

void GRAPHbfs(Graph G, int id) {
  int v, time=0, *pre, *st;
  pre = malloc(G->V*sizeof(int));
  st = malloc(G->V*sizeof(int));
  if ((pre == NULL) || (st == NULL))
    return;

  for (v=0; v < G->V; v++) {
    pre[v] = -1;
    st[v] = -1;
  }

  bfs(G, EDGEcreate(id,id), &time, pre, st);

  printf("\n Resulting BFS tree \n");
  for (v=0; v < G->V; v++)
    if (st[v] != -1)
      printf("%s's parent is: %s \n", STsearchByIndex(G->tab, v), STsearchByIndex(G->tab, st[v]));
}

static void bfs(Graph G, Edge e, int *time, int *pre, int *st) {
  int v;
  Q q = Qinit();
  Qput(q, e);
  while (!Qempty(q))
    if (pre[(e = Qget(q)).w] == -1) {
      pre[e.w] = (*time)++;
      st[e.w] = e.v;
      for (v = 0; v < G->V; v++)
        if (G->madj[e.w][v] == 1)
          if (pre[v] == -1)
            Qput(q, EDGEcreate(e.w, v));
    }
  Qfree(q);
}
