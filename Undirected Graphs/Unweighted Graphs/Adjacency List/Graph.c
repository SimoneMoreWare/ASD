#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Graph.h"
#define MAXC 11


typedef struct node *link;
struct node { int v; link next; } ;
struct graph { int V; int E; link *ladj; ST tab; link z; } ;

static link  NEW(int v, link next);
static Edge  EDGEcreate(int v, int w);
static void  insertE(Graph G, Edge e);
static void  removeE(Graph G, Edge e);
static void  dfsR(Graph G, Edge e, int *time, int *pre, int *post, int *st);
static void  dfsRcc(Graph G, int v, int id, int *cc);

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

Graph GRAPHinit(int V) {
  int v;
  Graph G = malloc(sizeof *G);
  if (G == NULL)
    return NULL;

  G->V = V;
  G->E = 0;
  G->z = NEW(-1, NULL);
  if (G->z == NULL)
    return NULL;
  G->ladj = malloc(G->V*sizeof(link));
  if (G->ladj == NULL)
    return NULL;
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

void GRAPHinsertE(Graph G, int id1, int id2) {
  insertE(G, EDGEcreate(id1, id2));
}

void GRAPHremoveE(Graph G, int id1, int id2) {
  removeE(G, EDGEcreate(id1, id2));
}

static void  insertE(Graph G, Edge e) {
  int v = e.v, w = e.w;

  G->ladj[v] = NEW(w, G->ladj[v]);
  G->ladj[w] = NEW(v, G->ladj[w]);
  G->E++;
}

static void  removeE(Graph G, Edge e) {
  int v = e.v, w = e.w;
  link x;
  if (G->ladj[v]->v == w) {
    G->ladj[v] = G->ladj[v]->next;
    G->E--;
  }
  else
    for (x = G->ladj[v]; x != G->z; x = x->next)
      if (x->next->v == w) {
        x->next = x->next->next;
        G->E--;
      }
  if (G->ladj[w]->v == v)
    G->ladj[w] = G->ladj[w]->next;
  else
    for (x = G->ladj[w]; x != G->z; x = x->next)
      if (x->next->v == v)
        x->next = x->next->next;
}

void  GRAPHedges(Graph G, Edge *a) {
  int v, E = 0;
  link t;
  for (v=0; v < G->V; v++)
    for (t=G->ladj[v]; t != G->z; t = t->next)
      if (v < t->v)
        a[E++] = EDGEcreate(v, t->v);
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

static void dfsR(Graph G, Edge e, int *time, int *pre, int *post, int *st) {
  link t; int v, w = e.w; Edge x;
  if (e.v != e.w)
    printf("edge (%s, %s) is tree \n", STsearchByIndex(G->tab, e.v), STsearchByIndex(G->tab, e.w)) ;
  st[e.w] = e.v;
  pre[w] = (*time)++;
  for (t = G->ladj[w]; t != G->z; t = t->next)
    if (pre[t->v] == -1)
      dfsR(G, EDGEcreate(w, t->v), time, pre, post, st);
    else {
      v = t->v;
      x = EDGEcreate(w, v);
      if (post[v] == -1)
        printf("edge (%s, %s) is back \n", STsearchByIndex(G->tab, x.v), STsearchByIndex(G->tab, x.w));
      else
        if(pre[v]>pre[w])
          printf("edge (%s, %s) is forward \n", STsearchByIndex(G->tab, x.v), STsearchByIndex(G->tab, x.w));
        else
          printf("edge (%s, %s) is cross \n", STsearchByIndex(G->tab, x.v), STsearchByIndex(G->tab, x.w));
    }
  post[w] = (*time)++;
}

void GRAPHdfs(Graph G, int id) {
  int v, time=0, *pre, *post, *st;
  pre = malloc(G->V * sizeof(int));
  post = malloc(G->V * sizeof(int));
  st = malloc(G->V * sizeof(int));
  if ((pre == NULL) || (post == NULL) || (st == NULL))
    return;

  for (v=0; v < G->V; v++) {
    pre[v] = -1;
    post[v] = -1;
    st[v] =  -1;
  }

  dfsR(G, EDGEcreate(id,id), &time, pre, post, st);

  for (v=0; v < G->V; v++)
    if (pre[v]== -1)
      dfsR(G, EDGEcreate(v,v), &time, pre, post, st);

  printf("discovery/endprocessing time labels \n");
  for (v=0; v < G->V; v++)
    printf("vertex %s : %d/%d \n", STsearchByIndex(G->tab, v), pre[v], post[v]);

  printf("resulting DFS tree \n");
  for (v=0; v < G->V; v++)
     printf("parent of vertex %s is vertex  %s \n", STsearchByIndex(G->tab, v), STsearchByIndex(G->tab, st[v]));
}

int GRAPHcc(Graph G) {
  int v, id = 0, *cc;
  cc = malloc(G->V * sizeof(int));
  if (cc == NULL)
    return -1;

  for (v = 0; v < G->V; v++)
    cc[v] = -1;

  for (v = 0; v < G->V; v++)
    if (cc[v] == -1)
      dfsRcc(G, v, id++, cc);

  printf("Connected component(s) \n");
  for (v = 0; v < G->V; v++)
    printf("node %s belongs to cc %d \n", STsearchByIndex(G->tab, v), cc[v]);
  return id;
}

static void dfsRcc(Graph G, int v, int id, int *cc) {
  link t;
  cc[v] = id;
  for (t = G->ladj[v]; t != G->z; t = t->next)
    if (cc[t->v] == -1)
      dfsRcc(G, t->v, id, cc);
}


