#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "DAG.h"

#define MAXC 10

typedef struct node *link;
struct node { int v; link next; } ;
struct dag { int V; int E; link *ladj; ST tab; link z; } ;

static Edge  EDGEcreate(int v, int w);
static link  NEW(int v, link next);
static void  insertE(Dag D, Edge e);
static void  removeE(Dag D, Edge e);

static Edge EDGEcreate(int v, int w) {
  Edge e;
  e.v = v;
  e.w = w;
  return e;
}

static link NEW(int v, link next) {
  link x = malloc(sizeof *x);
  if (x == NULL)
    return NULL;
  x->v = v;
  x->next = next;
  return x;
}

Dag DAGinit(int V) {
  int v;
  Dag D = malloc(sizeof *D);
  if (D == NULL)
    return NULL;

  D->V = V;
  D->E = 0;
  D->z = NEW(-1, NULL);
  if (D->z == NULL)
    return NULL;
  D->ladj = malloc(D->V*sizeof(link));
  if (D->ladj == NULL)
    return NULL;
  for (v = 0; v < D->V; v++)
    D->ladj[v] = D->z;
  D->tab = STinit(V);
  if (D->tab == NULL)
    return NULL;
  return D;
}

void DAGfree(Dag D) {
  int v;
  link t, next;
  for (v=0; v < D->V; v++)
    for (t=D->ladj[v]; t != D->z; t = next) {
      next = t->next;
      free(t);
    }
  STfree(D->tab);
  free(D->ladj);
  free(D->z);
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

  D->ladj[v] = NEW(w, D->ladj[v]);
  D->E++;
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
  link x;
  if (D->ladj[v]->v == w) {
    D->ladj[v] = D->ladj[v]->next;
    D->E--;
  }
  else
    for (x = D->ladj[v]; x != D->z; x = x->next)
      if (x->next->v == w) {
        x->next = x->next->next;
        D->E--;
  }
}

void  DAGedges(Dag D, Edge *a) {
  int v, E = 0;
  link t;
  for (v=0; v < D->V; v++)
    for (t=D->ladj[v]; t != D->z; t = t->next)
      a[E++] = EDGEcreate(v, t->v);
}

void TSdfsR(Dag D, int v, int *ts, int *pre, int *time) {
  link t;
  pre[v] = 0;
  for (t = D->ladj[v]; t != D->z; t = t->next)
    if (pre[t->v] == -1)
      TSdfsR(D, t->v, ts, pre, time);
  ts[(*time)++] = v;
}

void DAGrts(Dag D) {
  int v, time = 0, *pre, *ts;
  pre = malloc(D->V*sizeof(int));
  ts = malloc(D->V*sizeof(int));
  if ((pre == NULL) || (ts == NULL))
    return;

  for (v=0; v < D->V; v++) {
    pre[v] = -1;
    ts[v] = -1;
  }
  for (v=0; v < D->V; v++)
    if (pre[v]== -1)
      TSdfsR(D, v, ts, pre, &time);

  printf("DAG nodes in reverse topological order \n");
  for (v=0; v < D->V; v++)
    printf("%s ", STsearchByIndex(D->tab, ts[v]));
  printf("\n");

}
