#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Graph.h"
#include "ST.h"
#include "PQ.h"

struct G {
  int V;
  int **madj; /* traccia esistenza di arco (0 assente, 1 presente, 2 temporaneo) */
  int **wadj; /* traccia effettivo peso dell'arco (non sono noti range per i pesi) */
  int *deleted;
};

static int **MATRIXint(int r, int c, int val);
static void  insertE(Graph G, Edge e);
static Edge  EDGEcreate(int v, int w, int wt);

static int **MATRIXint(int r, int c, int val) {
  int i, j, **t;
  t = malloc(r * sizeof(int *));
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
  Graph g = malloc(sizeof(*g));
  if (g == NULL)
    return NULL;
  g->V = V;
  g->madj = MATRIXint(V, V, 0);
  if (g->madj == NULL)
    return NULL;
  g->wadj = MATRIXint(V, V, 0);
  if (g->wadj == NULL)
    return NULL;
  g->deleted = calloc(V, sizeof(int));
  if (g->deleted == NULL)
    return NULL;
  return g;
}

void GRAPHfree(Graph G) {
  int i;
  for (i=0; i<G->V; i++) {
    free(G->madj[i]);
    free(G->wadj[i]);
  }
  free(G->madj);
  free(G->wadj);
  free(G->deleted);
  free(G);
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
  insertE(G, EDGEcreate(id1, id2, wt));
}

static void  insertE(Graph g, Edge e) {
  int v = e.v, w = e.w, wt = e.wt;
  g->madj[v][w] = 1;
  g->madj[w][v] = 1;
  g->wadj[v][w] = wt;
  g->wadj[w][v] = wt;
}

static Edge EDGEcreate(int v, int w, int wt) {
  Edge e;
  e.v = v;
  e.w = w;
  e.wt = wt;
  return e;
}

int *GRAPHssspD(Graph g, int s) {
  int nV = g->V, v, w, *mindist;
  PQ pq = PQinit(g->V);
  if (pq == NULL)
    return NULL;
  mindist = calloc(nV, sizeof(int));
  if (mindist == NULL)
    return NULL;

  for (v = 0; v < g->V; v++) {
    mindist[v] = INT_MAX;
    PQinsert(pq, mindist, v);
  }

  mindist[s] = 0;
  PQchange(pq, mindist, s);

  while (!PQempty(pq)) {
    if (mindist[v = PQextractMin(pq, mindist)] != INT_MAX) {
      for (w = 0; w < g->V; w++)
        if (g->madj[v][w] !=0)
          if (mindist[v] + g->wadj[v][w] < mindist[w]) {
            mindist[w] = mindist[v] + g->wadj[v][w];
            PQchange(pq, mindist, w);
          }
    }
  }
  PQfree(pq);
  return mindist;
}

int **GRAPHapspFW(Graph g) {
  int nV = g->V, i, j, k, **dist;

  dist = calloc(nV, sizeof(int*));
  if (dist == NULL)
    return NULL;

  for(i=0;i<nV;i++) {
    dist[i] = calloc(nV, sizeof(int));
    if (dist[i] == NULL)
      return NULL;
  }

  for(i=0;i<nV;i++) {
    for(j=i+1;j<nV;j++) {
      dist[i][j] = dist[j][i] = (g->madj[i][j] ? g->wadj[i][j] : INT_MAX);
    }
  }

  for(i=0;i<nV;i++) {
    for(j=0;j<nV;j++) {
      for(k=0;k<nV;k++) {
        if (dist[i][k] == INT_MAX) continue;
        if (dist[k][j] == INT_MAX) continue;
        dist[i][j] = (dist[i][j] > dist[i][k] + dist[k][j]) ? (dist[i][k] + dist[k][j]) : (dist[i][j]);
      }
    }
  }
  return dist;
}

int GRAPHgetNumV(Graph g) {
  if (g == NULL)
    return -1;
  return g->V;
}

void dfsR(Graph g, int start, int *cc, int id, int time, int *pre, int *isAcyclic) {
  int v;
  cc[start] = id;
  pre[start] = time++;
  for (v=0; v<g->V;v++) {
    if (g->deleted[v] != 1 && g->madj[start][v] != 0) {
      if (cc[v] == -1)
        dfsR(g, v, cc, id, time, pre, isAcyclic);
      else {
        if (pre[start] < pre[v])
          *isAcyclic = 0;
      }
    }
  }
}

int *GRAPHdfs(Graph g, int *nCC, int *isAcyclic) {
  int *cc, *pre, v, id = 0;
  if (g == NULL)
    return NULL;
  if (g->madj == NULL)
    return NULL;
  cc = calloc(g->V, sizeof(int));
  pre = calloc(g->V, sizeof(int));
  if (cc == NULL || pre == NULL)
    return NULL;
  for(v=0;v<g->V;v++)
    cc[v] = pre[v] = -1;

  for(v=0;v<g->V;v++) {
    if (g->deleted[v] != 1)
      if (cc[v] == -1)
        dfsR(g, v, cc, id++, 0, pre, isAcyclic);
  }
  *nCC = id;
  free(pre);
  return cc;
}

void GRAPHdeleteV(Graph g, int *set, int k) {
  int i;
  if (g == NULL)
    return;
  if (g->deleted == NULL)
    return;
  for(i=0;i<k;i++) {
    if (set[i] < g->V)
      g->deleted[set[i]] = 1;
  }
}

void GRAPHreset(Graph g) {
  int i;
  if (g == NULL) return;
  if (g->deleted == NULL) return;
  for(i=0;i<g->V;i++) {
    g->deleted[i] = 0;
  }
}

void combE(Graph g, Edge *all, int *sol, int *best, int pos, int start, int k, int E, int *sum, int **dist, char **tab) {
  int i, j, v, w;
  int nCC2, a = 1, currSum = 0;
  int *cc2;
  if (pos >= k) {
    for(i=0;i<k;i++) {
      v = all[sol[i]].v;
      w = all[sol[i]].w;
      g->madj[v][w] = 2;
      g->wadj[v][w] = dist[v][w];
    }

    cc2 = GRAPHdfs(g, &nCC2, &a);
    free(cc2);

    if (nCC2 > 1 || a == 0) {
      /* Set di archi non idoneo a riconnettere il grafo */
    } else {
      /* Calcola somma degli archi attualmente nel grafo */
      for(i=0;i<g->V-1;i++) {
        if (!g->deleted[i])
          for(j=i+1;j<g->V;j++) {
            if (!g->deleted[j])
              if (g->madj[i][j] != 0)
                currSum += g->wadj[i][j];
          }
      }
      /* Se soluzione migliorante o prima soluzione funzionante, aggiorna */
      if (*sum == -1 || currSum < *sum) {
        printf("\t");
        for(i=0;i<k;i++)
          printf("(%s,%s) ", tab[all[sol[i]].v], tab[all[sol[i]].w]);
        if (*sum == -1)
          printf(" Improvement - current weight = %d < previous weight = INF \n", currSum);
        else
          printf(" Improvement - current weight = %d < previous weight  %d \n", currSum, *sum);
        *sum = currSum;
        memcpy(best, sol, k*sizeof(int));
      }
    }

    for(i=0;i<k;i++) {
      v = all[sol[i]].v;
      w = all[sol[i]].w;
      g->madj[v][w] = 0;
      g->wadj[v][w] = 0;
    }

    return;
  }
  for(i=start;i<E;i++) {
    sol[pos] = i;
    combE(g, all, sol, best, pos+1, i+1, k, E, sum, dist, tab);
  }
}

void GRAPHconnect(Graph g, int *cc, int nCC, int *sum, Edge *best, int *eNum, int **dist, char **tab) {
  int i, j, choices = 0;
  Edge *allEdges = calloc(g->V*g->V, sizeof(Edge));
  int *sol = calloc(nCC-1, sizeof(int));
  int *bestsol = calloc(nCC-1, sizeof(int));
  if (allEdges == NULL || sol == NULL || bestsol == NULL)
    exit(-1);
  /* Generazione di tutti gli archi ammissibili per la riconnessione */
  /* tra vertici non eliminati e non già appartenenti alla stessa cc */
  for(i=0;i<g->V-1;i++) {
    if (!g->deleted[i])
      for(j=i+1;j<g->V;j++) {
        if (!g->deleted[j])
          if (cc[i] != cc[j]) {
            allEdges[choices].v = i;
            allEdges[choices++].w = j;
          }
      }
  }

  /* Calcolo della migliore combinazione di vertici da aggiungere (potenzialmente set vuoto se nCC == 1) */
  combE(g, allEdges, sol, bestsol, 0, 0, nCC-1, choices, sum, dist, tab);

  for(i=0;i<nCC-1;i++) {
    best[i].v = allEdges[bestsol[i]].v;
    best[i].w = allEdges[bestsol[i]].w;
  }
  *eNum = nCC-1;

  free(sol);
  free(bestsol);
  free(allEdges);
  return;
}
