#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "DAG.h"

#define MAXC 10

struct dag {int V; int E; int **madj; ST tab; };

static Edge  EDGEcreate(int v, int w);
static int **MATRIXint(int r, int c, int val);
static void  insertE(Dag D, Edge e);
static void  removeE(Dag D, Edge e);

static Edge EDGEcreate(int v, int w) {
  Edge e;
  e.v = v;
  e.w = w;
  return e;
}

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

Dag DAGinit(int V) {
  Dag D = malloc(sizeof *D);
  if (D == NULL)
    return NULL;
  D->V = V;
  D->E = 0;
  D->madj = MATRIXint(V, V, 0);
  if (D->madj == NULL)
    return NULL;
  D->tab = STinit(V);
  if (D->tab == NULL)
    return NULL;
  return D;
}

void DAGfree(Dag D) {
  int i;
  for (i=0; i<D->V; i++)
    free(D->madj[i]);
  free(D->madj);
  STfree(D->tab);
  free(D);
}

Dag DAGload(FILE *fin) {
  int V, i, id1, id2;
  char label1[MAXC], label2[MAXC];
  Dag D;

  fscanf(fin, "%d", &V);
  D = DAGinit(V);

  for (i=0; i<V; i++) {
    fscanf(fin, "%s", label1);
    STinsert(D->tab, label1, i);
  }

  while(fscanf(fin, "%s %s", label1, label2) == 2) {
    id1 = STsearch(D->tab, label1);
    id2 = STsearch(D->tab, label2);
    if (id1 >= 0 && id2 >=0)
      DAGinsertE(D, id1, id2);
  }
  return D;
}

static void  insertE(Dag D, Edge e) {
  int v = e.v, w = e.w;

  if (D->madj[v][w] == 0)
    D->E++;
  D->madj[v][w] = 1;
}

void DAGstore(Dag D, FILE *fout) {
  int i;
  Edge *a;

  a = malloc(D->E * sizeof(Edge));
  if (a == NULL)
    return;

  DAGedges(D, a);

  fprintf(fout, "%d\n", D->V);
  for (i = 0; i < D->V; i++)
    fprintf(fout, "%s\n", STsearchByIndex(D->tab, i));

  for (i = 0; i < D->E; i++)
    fprintf(fout, "%s  %s\n", STsearchByIndex(D->tab, a[i].v), STsearchByIndex(D->tab, a[i].w));

}

int DAGgetIndex(Dag D, char *label) {
  int id;
  id = STsearch(D->tab, label);
  if (id == -1) {
    id = STsize(D->tab);
    STinsert(D->tab, label, id);
  }
  return id;
}

void DAGinsertE(Dag D, int id1, int id2) {
  insertE(D, EDGEcreate(id1, id2));
}

void DAGremoveE(Dag D, int id1, int id2) {
  removeE(D, EDGEcreate(id1, id2));
}

static void  removeE(Dag D, Edge e) {
  int v = e.v, w = e.w;
  if (D->madj[v][w] == 1)
    D->E--;
  D->madj[v][w] = 0;
}

void  DAGedges(Dag D, Edge *a) {
  int v, w, E = 0;
  for (v=0; v < D->V; v++)
    for (w=0; w < D->V; w++)
      if (D->madj[v][w] == 1)
        a[E++] = EDGEcreate(v, w);
}

void TSdfsR(Dag D, int v, int *ts, int *pre, int *time) {
  int w;
  pre[v] = 0;
  for (w  = 0; w < D->V; w++)
    if (D->madj[w][v]  != 0)
      if (pre[w] == -1)
        TSdfsR(D, w, ts, pre, time);
  ts[(*time)++] = v;
}

void DAGts(Dag D) {
  int v, time = 0, *pre, *ts;
  pre = malloc(D->V*sizeof(int));
  ts = malloc(D->V*sizeof(int));
  if ((pre == NULL) || (ts == NULL))
    return;

  for (v=0; v < D->V; v++) {
    pre[v] = -1;
    ts[v] = -1;
  }
  for (v=0; v <D->V; v++)
    if (pre[v]== -1)
      TSdfsR(D, v, ts, pre, &time);

  printf("DAG nodes in topological order \n");
  for (v=0; v < D->V; v++)
     printf("%s ", STsearchByIndex(D->tab, ts[v]));
  printf("\n");

}

