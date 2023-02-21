#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include "Graph.h"

#define MAXC 21

typedef struct edge { int v; int w; } Edge;

struct graph {int V; int E; int **madj; ST tab; };

static int **MATRIXint(int r, int c, int val);
static void  insertE(Graph G, Edge e);
static Edge  EDGEcreate(int v, int w);
static void  pathR(Graph G, int currv, int start, int *currpath, int currlen, int currval, int *bestpath, int *bestlen, int *bestval, int *visited);

static Edge EDGEcreate(int v, int w) {
  Edge e;
  e.v = v;
  e.w = w;
  return e;
}

static void  insertE(Graph G, Edge e) {
  int v = e.v, w = e.w;

  if (G->madj[v][w] == 0)
    G->E++;
  G->madj[v][w] = 1;
  G->madj[w][v] = 1;
}

static int **MATRIXint(int r, int c, int val) {
  int i, j;
  int **t = malloc(r * sizeof(int *));
  if (t == NULL) return NULL;
  for (i=0; i < r; i++) {
    t[i] = malloc(c * sizeof(int));
    if (t[i] == NULL) return NULL;
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
  STfree(G->tab);
  for (i=0; i<G->V; i++)
    free(G->madj[i]);
  free(G->madj);
  free(G);
}

Graph GRAPHload(FILE *fin) {
  int S, i, id1, id2, v, m;
  char label1[MAXC], label2[MAXC];
  Graph G;

  fscanf(fin, "%d", &S);
  G = GRAPHinit(S);
  if (G == NULL) return NULL;
  for (i=0; i<S; i++) {
    fscanf(fin, "%s %d %d", label1, &v, &m);
    STinsert(G->tab, label1, v, m, i);
  }

  while(fscanf(fin, "%s %s ", label1, label2) == 2) {
    id1 = STsearch(G->tab, label1);
    id2 = STsearch(G->tab, label2);
    if (id1 >= 0 && id2 >=0)
      insertE(G, EDGEcreate(id1, id2));
  }
  return G;
}

void GRAPHpath(Graph G) {
  int *visited, *bestpath, *currpath, len = 0, val = 0, i, V;

  printf("Inserisci punti-ferita iniziali: ");
  scanf("%d", &V);

  visited = calloc(G->V, sizeof(int));
  bestpath = calloc(G->V, sizeof(int));
  currpath = calloc(G->V, sizeof(int));
  if (visited == NULL || bestpath == NULL || currpath == NULL) exit(-1);
  pathR(G, V, 0, currpath, 0, 0, bestpath, &len, &val, visited);

  printf("Cammino migliore: %d monete d'oro\n", val);
  printf("%s\n", STsearchNameByIndex(G->tab, 0));
  for(i=0; i<len; i++)
    printf("%s\n", STsearchNameByIndex(G->tab, bestpath[i]));

  free(bestpath);
  free(visited);
  free(currpath);
  return;
}

void pathR(Graph G, int currv, int start, int *currpath, int currlen, int currval, int *bestpath, int *bestlen, int *bestval, int *visited) {
  int i;
  if (start == (G->V-1)) {
    if (currval > *bestval) {
      *bestlen = currlen;
      *bestval = currval;
      for (i=0; i < currlen; i++)
        bestpath[i] = currpath[i];
    }
    return;
  }

  visited[start] = 1;
  for (i = 0 ; i < G->V ; i++)
    if (G->madj[start][i] == 1)
      if (visited[i] == 0)
        if (STsearchPointsByIndex(G->tab, i)< currv) {
          currpath[currlen] = i;
          pathR(G, currv-STsearchPointsByIndex(G->tab, i), i, currpath, currlen+1, currval+STsearchValueByIndex(G->tab, i),
            bestpath, bestlen, bestval, visited);

        }
  visited[start] = 0;
  return;
}
