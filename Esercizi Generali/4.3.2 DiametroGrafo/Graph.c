#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "BST.h"
#include "Queue.h"
#include "Graph.h"
#define MAXC 21


typedef struct vertex { char name[MAXC]; int wt; } Vertex;

struct graph {int V; int E; int **madj; BST bst; Vertex *tab; };

static int   **MATRIXint(int r, int c, int val);
static void  insertE(Graph G, Edge e);
static Edge  EDGEcreate(int v, int w, int wt);
static int   bfs(Graph G, Edge e, int *time, int *pre, int *dist);
static void  allPathsR(Graph G, int src, Edge *path, int *visited, int curLen, int curVal, Edge *bestPath, int *bestLen, int *bestVal);

static int **MATRIXint(int r, int c, int val) {
  int i, j;
  int **t = malloc(r * sizeof(int *));
  if (t == NULL)
    return NULL;

  for (i=0; i < r; i++) {
    t[i] = malloc(c * sizeof(int));
    if (t[i] == NULL)
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
  G->bst = BSTinit();
  if (G->bst == NULL)
    return NULL;
  G->tab = malloc(V * sizeof(Vertex));
  if (G->tab == NULL)
    return NULL;
  return G;
}

void GRAPHfree(Graph G) {
  int i;
  free(G->tab);
  BSTfree(G->bst);
  for (i=0; i<G->V; i++)
    free(G->madj[i]);
  free(G->madj);
  free(G);
}

Graph GRAPHload(FILE *fin) {
  int V, i, id1, id2, wt;
  char label1[MAXC], label2[MAXC];
  Graph G;

  fscanf(fin, "%d", &V);
  G = GRAPHinit(V);
  if (G == NULL) return NULL;
  for (i=0; i<V; i++) {
    fscanf(fin, "%s %d", label1, &wt);
    BSTinsert(G->bst, label1, i);
    strcpy(G->tab[i].name, label1);
    G->tab[i].wt = wt;
  }

  while(fscanf(fin, "%s %s %d", label1, label2, &wt) == 3) {
    id1 = BSTsearch(G->bst, label1);
    id2 = BSTsearch(G->bst, label2);
    if (id1 >= 0 && id2 >=0)
      insertE(G, EDGEcreate(id1, id2, wt));
  }
  return G;
}

int GRAPHnumV(Graph G) {
  return G->V;
}

char *GRAPHsearchByIndex(Graph G, int i) {
  return G->tab[i].name;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
  insertE(G, EDGEcreate(id1, id2, wt));
}

static void  insertE(Graph G, Edge e) {
  int v = e.v, w = e.w, wt = e.wt;

  if (G->madj[v][w] == 0)
    G->E++;
  G->madj[v][w] = wt;
}

static Edge EDGEcreate(int v, int w, int wt) {
  Edge e;
  e.v = v;
  e.w = w;
  e.wt = wt;
  return e;
}

int GRAPHbfs(Graph G, int id) {
  int v, time=0, *pre, *dist, max;
  pre = malloc(G->V*sizeof(int));
  dist = malloc(G->V*sizeof(int));
  if (pre == NULL || dist == NULL)
   exit(-1);
  for (v=0; v < G->V; v++) {
    pre[v] = -1;
    dist[v] = -1;
  }
  max = bfs(G, EDGEcreate(id,id,0), &time, pre, dist);
  free(pre);
  free(dist);
  return max;
}

int bfs(Graph G, Edge e, int *time, int *pre, int *dist) {
  int v, maxdist = 0;
  Q q = QUEUEinit();
  if (q == NULL) exit(-1);
  QUEUEput(q, e);
  while (!QUEUEempty(q))
    if (pre[(e = QUEUEget(q)).w] == -1) {
      pre[e.w] = (*time)++;
      dist[e.w] = dist[e.v]+1;
      if (dist[e.w] > maxdist)
        maxdist = dist[e.w];
      for (v = 0; v < G->V; v++)
        if (G->madj[e.w][v] != 0)
          if (pre[v] == -1)
            QUEUEput(q, EDGEcreate(e.w, v, G->madj[e.w][v]));
    }
  QUEUEfree(q);
  return maxdist;
}

Edge* GRAPHlongestPath(Graph G, int src, int *len, int *val){
  Edge *path, *bestPath;
  int i, *visited;

  path = malloc(G->E * sizeof(Edge));
  bestPath = malloc(G->E * sizeof(Edge));
  visited = malloc(G->V * sizeof(int));
  if (path == NULL || bestPath == NULL || visited == NULL)
   exit(-1);
  for (i=0; i< G->V; i++)
    visited[i]=0;

  allPathsR(G, src, path, visited, 0, G->tab[src].wt, bestPath, len, val);

  free(visited);
  free(path);

  return bestPath;
}

static void allPathsR(Graph G, int src, Edge *path, int *visited, int curLen, int curVal, Edge *bestPath, int *bestLen, int *bestVal) {
  int i, t, terminal = 1;
  visited[src] = 1;

  for (t=0; t < G->V; t++) {
    if (G->madj[src][t] !=0)
      if (!visited[t]) {
        path[curLen] = EDGEcreate(src, t, G->madj[src][t]);
        allPathsR(G, t, path, visited, curLen+1, curVal+ G->tab[t].wt + G->madj[src][t], bestPath, bestLen, bestVal);
        terminal = 0;
	}
  }

  if (terminal) {
	if (*bestVal < curVal || *bestLen == -1) {
	  *bestVal = curVal;
	  *bestLen = curLen;
      for (i=0;i<curLen;i++)
        bestPath[i] = path[i];
    }
  }
  visited[src] = 0;
  curVal -= G->tab[src].wt;
}

