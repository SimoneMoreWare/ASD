#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Graph.h"
#include "ST.h"

struct graph { int V; int E; int **madj; int *scc; };

static int  **MATRIXint(int r, int c, int val);
static void   allPathsR(Graph g, int v, int w, int *visited, int *npaths, int *max, int *path, int currlen, int *currpath);
static void   insertE(Graph G, Edge e);
static void   removeE(Graph G, Edge e);
static Edge   EDGEcreate(int v, int w);
static int    simplComb(Graph kDAG, Graph g, ST tab, int pos, Edge *candEdges, int *sol, int n, int k, int start);
static int    check(Graph kDAG, Graph g,  ST tab, Edge *candEdges, int *sol, int n, int k);

int GRAPHnumV(Graph g) {
  if (g == NULL) return 0;
  return g->V;
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
  int v;
  Graph G = malloc(sizeof *G);
  if (G == NULL)
    return NULL;
  G->V = V;
  G->E = 0;
  G->scc = malloc(V * sizeof(int));
  if (G->scc == NULL) return NULL;
  for (v = 0; v < V; v++)
    G->scc[v] = -1;
  G->madj = MATRIXint(V, V, 0);
  if (G->madj == NULL) return NULL;
  return G;
}

void GRAPHfree(Graph G) {
  int i;
  for (i=0; i<G->V; i++)
    free(G->madj[i]);
  free(G->madj);
  free(G->scc);
  free(G);
}

void GRAPHremoveE(Graph G, int id1, int id2) {
  removeE(G, EDGEcreate(id1, id2));
}

static void  removeE(Graph G, Edge e) {
  int v = e.v, w = e.w;
  if (G->madj[v][w]==1)
    G->E--;
  G->madj[v][w] = 0;
}

void GRAPHinsertE(Graph G, int id1, int id2) {
  insertE(G, EDGEcreate(id1, id2));
}

static void  insertE(Graph G, Edge e) {
  int v = e.v, w = e.w;
  if (G->madj[v][w]==0)
    G->E++;
  G->madj[v][w] = 1;
}

static Edge EDGEcreate(int v, int w) {
  Edge e;
  e.v = v;
  e.w = w;
  return e;
}

int GRAPHlongestPathVW(Graph g, int v, int w, int *maxlen, int *path){
  int i, npaths = 0, *visited, *currpath;
  visited = malloc(g->V * sizeof(int));
  currpath = malloc(g->V * sizeof(int));
  if (visited == NULL || currpath == NULL) exit(-1);
  for (i=0; i<g->V; i++) {
    path[i] = currpath[i] = -1;
    visited[i] = 0;
  }

  allPathsR(g, v, w, visited, &npaths, maxlen, path, 0, currpath);
  free(visited);
  free(currpath);
  return npaths;
}

static void allPathsR(Graph g, int v, int w, int *visited, int *npaths, int *maxlen, int *path, int currlen, int *currpath) {
  int i;
  if (v == w) {
    (*npaths)++;
    currpath[currlen] = w;
    if (*maxlen == 0 || currlen > *maxlen) {
      *maxlen = currlen;
      for (i=0; i<g->V; i++)
        path[i] = currpath[i];
    }
    return;
  }

  visited[v] = 1;
  currpath[currlen] = v;

  for (i=0; i<g->V; i++) {
    if (g->madj[v][i]==1) {
      if (!visited[i]) {
        allPathsR(g, i, w, visited, npaths, maxlen, path, currlen+1, currpath);
      }
      visited[i] = 0;
    }
  }
}

Graph GRAPHreverse(Graph g) {
  int v, w;
  Graph r;

  r = GRAPHinit(g->V);
  if (r == NULL) return NULL;
  for (v=0; v<g->V; v++)
    for (w=0; w<g->V; w++)
      r->madj[w][v] = g->madj[v][w];
  return r;
}

void SCCdfsR(Graph g, int w, int *time0, int time1, int *post) {
  int v;
  g->scc[w] = time1;
  for (v=0; v<g->V; v++)
    if (g->madj[w][v])
      if (g->scc[v] == -1)
        SCCdfsR(g, v, time0, time1, post);
  post[(*time0)++]= w;
}

int GRAPHscc(Graph g, ST tab, int flag) {
  int v, time0 = 0, time1 = 0, *postG, *postR;
  Graph r;

  r = GRAPHreverse(g);
  if (r == NULL) exit(-1);

  postG = malloc (g->V * sizeof(int));
  postR = malloc (g->V * sizeof(int));
  if (postG == NULL || postR == NULL) exit(-1);
  for (v=0; v < g->V; v++) {
    g->scc[v] = -1;
    r->scc[v] = -1;
    postG[v] = -1;
    postR[v] = -1;
  }

  for (v=0; v < r->V; v++)
    if (r->scc[v] == -1)
      SCCdfsR(r, v, &time0, time1, postR);

  time0 = time1 = 0;

  for (v = g->V-1; v >= 0; v--)
    if (g->scc[postR[v]]==-1){
      SCCdfsR(g,postR[v], &time0, time1, postG);
      time1++;
    }
  if (flag)
    for (v = 0; v < g->V; v++) {
      if (tab == NULL)
        printf("Vertex %s in SCC %d\n", STsearchByIndex(tab, v), g->scc[v]);
      else
        printf("%s in SCC %d\n", STsearchByIndex(tab, v), g->scc[v]);
    }

  free(postG);
  free(postR);
  GRAPHfree(r);

  return time1;
}

void GRAPHturn2SCC(Graph g, ST tab) {
  int nSCC, *sol, i, j, nE=0;
  Graph kDAG;
  Edge *candidateEdges;

  nSCC = GRAPHscc(g, tab, 0);
  if (nSCC == 1) {
    printf("Strongly connected graph: no need to add edges\n");
    return;
  }

  kDAG = GRAPHinit(nSCC);

  candidateEdges = malloc((nSCC*nSCC -1) * sizeof(Edge));

  for (i=0; i<g->V; i++)
    for (j=0; j<g->V; j++)
      if (g->madj[i][j] && g->scc[i] != g->scc[j])
        GRAPHinsertE(kDAG, g->scc[i], g->scc[j]);

  for(i=0; i<kDAG->V; i++)
    for(j=0; j<kDAG->V; j++)
      if ((i!=j) && (kDAG->madj[i][j]==0)) {
        candidateEdges[nE].v = i;
        candidateEdges[nE++].w = j;
      }

  for (i=1; i<=kDAG->V; i++) {
    sol = calloc(nE, sizeof(int));
    if (simplComb(kDAG, g, tab, 0, candidateEdges, sol, nE, i, 0)) {
      GRAPHfree(kDAG);
      free(candidateEdges);
      free(sol);
      return;
    }
  }
}

static int check(Graph kDAG, Graph g,  ST tab, Edge *candidateEdges, int *sol, int n, int k) {
  int i, j, v, w;
  Edge *addedEdges;

  addedEdges= malloc(k*sizeof(Edge));
  if (addedEdges == NULL) exit(-1);

  for (i=0; i<k; i++) {
    for (j=0; j<g->V; j++) {
      if (g->scc[j] == candidateEdges[sol[i]].v)
        v = j;
      if (g->scc[j] == candidateEdges[sol[i]].w)
        w = j;
    }
    GRAPHinsertE(g, v, w);
    addedEdges[i]=EDGEcreate(v, w);
  }
  if (GRAPHscc(g, tab, 0) == 1) {
    printf("Success! Following edges added:\n");
    for (j=0; j<k; j++)
      printf("%s %s \n", STsearchByIndex(tab, addedEdges[j].v), STsearchByIndex(tab, addedEdges[j].w));
    free(addedEdges);
    return 1;
  }
  for (i=0; i<k; i++)
    GRAPHremoveE(g, addedEdges[i].v, addedEdges[i].w);

  free(addedEdges);
  return 0;
}

static int simplComb(Graph kDAG, Graph g,  ST tab, int pos, Edge *candidateEdges, int *sol, int n, int k, int start) {
  int i;
  if (pos >= k) {
    if (check(kDAG, g,  tab, candidateEdges, sol, n, k))
      return 1;
    return 0;
  }
  for (i=start; i<n; i++) {
    sol[pos] = i;
    if (simplComb(kDAG, g, tab, pos+1, candidateEdges, sol, n, k, i+1))
      return 1;
  }
  return 0;
}
