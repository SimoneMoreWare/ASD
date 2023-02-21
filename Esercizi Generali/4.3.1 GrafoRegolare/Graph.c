#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"

typedef struct node *link;
struct node { int v; int wt; link next; } ;
struct graph { int V; int E; link *ladj; ST tab; link z; } ;

static Edge EDGEcreate(int v, int w, int wt);
static link NEW(int v, int wt, link next);
static void insertE(Graph G, Edge e);
static void allPathsR(Graph G, int src, Edge *path, int *visited, int curLen, int curW, Edge *bestPath, int *bestLen, int *bestW);

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
  if (G == NULL)
    return NULL;

  G->V = V;
  G->E = 0;
  G->z = NEW(-1, 0, NULL);
  if (G->z == NULL) return NULL;
  G->ladj = malloc(G->V*sizeof(link));
  if (G->ladj == NULL) return NULL;
  for (v = 0; v < G->V; v++)
    G->ladj[v] = G->z;
  G->tab = STinit(V);
  if (G->tab == NULL)
    return NULL;
  return G;
}

void GRAPHfree(Graph G) {
  int v;
  link t, next;
  for (v=0; v < G->V; v++)
    for (t=G->ladj[v]; t != G->z; t = next) {
      next = t->next;
      free(t);
    }
  STfree(G->tab);
  free(G->ladj);
  free(G->z);
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
    fscanf(fin, "%s", label1);
    STinsert(G->tab, label1, i);
  }

  while(fscanf(fin, "%s %s %d", label1, label2, &wt) == 3) {
    id1 = STsearch(G->tab, label1);
    id2 = STsearch(G->tab, label2);
    if (id1 >= 0 && id2 >=0)
      insertE(G, EDGEcreate(id1, id2, wt));
  }
  return G;
}

int GRAPHsearchByKey(Graph G, char *label) {
  int id;
  id = STsearch(G->tab, label);
  return id;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
  insertE(G, EDGEcreate(id1, id2, wt));
}

static void  insertE(Graph G, Edge e) {
  int v = e.v, w = e.w, wt = e.wt;

  G->ladj[v] = NEW(w, wt, G->ladj[v]);
  G->E++;
}

int  GRAPHregular(Graph G) {
  int v, *in_d, *out_d, reg=1;
  link t;

  in_d = malloc(G->V * sizeof(int));
  out_d = malloc(G->V * sizeof(int));

  if (in_d == NULL || out_d == NULL)
    exit(-1);

  for (v=0; v < G->V; v++) {
    in_d[v]=0;
    out_d[v] = 0;
  }

  for (v=0; v < G->V; v++)
    for (t=G->ladj[v]; t != G->z; t = t->next) {
      out_d[v]++;
      in_d[t->v]++;
    }

    for (v=0; v < G->V; v++)
      if ((in_d[v] != out_d[v]) || in_d[v] != in_d[0]) {
        reg = 0;
        break;
      }

  free(in_d);
  free(out_d);

  return reg;
}

void GRAPHlongestPath(Graph G, int src){
  int i, *visited, len = -1, weight = 0;
  Edge *path, *bestPath;

  path = malloc(G->E * sizeof(Edge));
  bestPath = malloc(G->E * sizeof(Edge));
  visited = malloc(G->V * sizeof(int));

  if (path == NULL || bestPath == NULL || visited == NULL)
    exit(-1);

  for (i=0; i< G->V; i++)
    visited[i]=0;

  allPathsR(G, src, path, visited, 0, 0, bestPath, &len, &weight);

  if (path != NULL && len > 0) {
    for(i=0; i<len; i++)
      fprintf(stdout,"%s -- <w=%d> -- %s\n", STsearchByIndex(G->tab,path[i].v), path[i].wt, STsearchByIndex(G->tab,path[i].w));
    fprintf(stdout, "Total weight: %d\n", weight);
  }
  else
    printf("No path found...\n");

  free(visited);
  free(path);
  free(bestPath);
}

static void allPathsR(Graph G, int src, Edge *path, int *visited, int curLen, int curW, Edge *bestPath, int *bestLen, int *bestW) {
  int i, terminal = 1;
  link t;
  visited[src] = 1;

  for (t=G->ladj[src]; t != G->z; t = t->next)
    if (!visited[t->v]) {
	  path[curLen] = EDGEcreate(src, t->v, t->wt);
	  allPathsR(G, t->v, path, visited, curLen+1, curW+t->wt, bestPath, bestLen, bestW);
	  terminal = 0;
    }

  if (terminal)
    if (*bestW < curW || *bestLen == -1) {
	  *bestW = curW;
	  *bestLen = curLen;
	  for (i=0;i<curLen;i++)
        bestPath[i] = path[i];
    }

  visited[src] = 0;
}


