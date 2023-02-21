#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Graph.h"

#define MAXC 10
#define maxE 100

typedef struct node *link;
struct node { int v; link next; } ;
struct graph { int V; int E; link *ladj; ST tab; link z; } ;

static Edge  EDGEcreate(int v, int w);
static link  NEW(int v, link next);
static void  insertE(Graph G, Edge e);
static void  removeE(Graph G, Edge e);
static void  dfsR(Graph G, Edge e, int *time, int *pre, int *post, int *st);
static void  SCCdfsR(Graph G, int w, int *scc, int *time0, int time1, int *post);
static Graph reverse(Graph G, Graph R);

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

static void  insertE(Graph G, Edge e) {
  int v = e.v, w = e.w;

  G->ladj[v] = NEW(w, G->ladj[v]);
  G->E++;
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

void  GRAPHedges(Graph G, Edge *a) {
  int v, E = 0;
  link t;
  for (v=0; v < G->V; v++)
    for (t=G->ladj[v]; t != G->z; t = t->next)
      a[E++] = EDGEcreate(v, t->v);
}

static Graph reverse(Graph G, Graph R) {
  int v;
  link t;
  for (v=0; v < G->V; v++)
    for (t= G->ladj[v]; t != G->z; t = t->next)
      GRAPHinsertE(R, t->v, v);
  return R;
}

static void SCCdfsR(Graph G, int w, int *scc, int *time0, int time1, int *post) {
  link t;
  scc[w] = time1;
  for (t = G->ladj[w]; t != G->z; t = t->next)
    if (scc[t->v] == -1)
      SCCdfsR(G, t->v, scc, time0, time1, post);
  post[(*time0)++]= w;
}

int GRAPHscc(Graph G) {
  int v, time0 = 0, time1 = 0, *sccG, *sccR, *postG, *postR;
  Graph R;

  R = GRAPHinit(G->V);
  reverse(G, R);

  sccG = malloc(G->V * sizeof(int));
  sccR = malloc(G->V * sizeof(int));
  postG = malloc(G->V * sizeof(int));
  postR = malloc(G->V * sizeof(int));

  for (v=0; v < G->V; v++) {
    sccG[v] = -1;
    sccR[v] = -1;
    postG[v] = -1;
    postR[v] = -1;
  }

  for (v=0; v < G->V; v++)
    if (sccR[v] == -1)
      SCCdfsR(R, v, sccR, &time0, time1, postR);

  time0 = 0;
  time1 = 0;

  for (v = G->V-1; v >= 0; v--)
    if (sccG[postR[v]]==-1){
      SCCdfsR(G,postR[v], sccG, &time0, time1, postG);
      time1++;
    }
  printf("strongly connected components \n");
  for (v = 0; v < G->V; v++)
    printf("node %s in scc %d \n", STsearchByIndex(G->tab, v), sccG[v]);
  GRAPHfree(R);
  return time1;
 }
