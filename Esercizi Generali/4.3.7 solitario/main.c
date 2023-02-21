#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Graph.h"
#include "ST.h"


#define MAXC 21
#define MAXM 5

typedef struct prize prize_t;
typedef struct graphPlus *GraphPlus;
typedef struct node node_t;

struct graphPlus {
  int V, E, C;
  Graph graph;
  ST stV;
  ST stC;
  node_t *nodes;
  Edge *edges;
};

struct node {
  char *name;
  int firstEdge;
  int prizeNum;
  prize_t *prizeList;
  int visited;
};

struct prize {
  int val;
  int cat;
  int used;
  prize_t *next;
};

GraphPlus read_file(char *fileName);
int       simplePath(GraphPlus g, int *prizes, int *path, int i, int move);
int       allPrizes(int *prizes, int nc);
int       bestPath(GraphPlus g, int *prizes, int i, int move, int score, int best);
int       EDGEScmp(GraphPlus g, Edge e1, Edge e2);
Edge     *EDGEsort(GraphPlus g);
void      freeAll(GraphPlus g);


int main(void) {
  int i, cmd, src, dst, len, best, *path, *prizes;
  char name[MAXC];
  Edge *sortedEdges;
  GraphPlus g;

  printf("Input file name: ");
  scanf("%s", name);

  g = read_file(name);
  if (g == NULL) exit(-1);

  do {
    printf("Options:\n");
    printf("  0. stop\n");
    printf("  1. list sorted edges\n");
    printf("  2. path with vertices associated to all prize categories\n");
    printf("  3. maximum possible score\n");
    printf("Command: ");
    scanf("%d", &cmd);
    switch (cmd) {
    case 0: break;
    case 1:
      printf("Sorted edges:\n");
      sortedEdges = EDGEsort(g);
      if (sortedEdges == NULL) exit(-1);
      for (i=0; i<g->E; i++) {
        src = sortedEdges[i].v;
        dst = sortedEdges[i].w;
        printf("%s %s\n", g->nodes[src].name, g->nodes[dst].name);
      }
      free(sortedEdges);
      printf("\n");
      break;
    case 2:
      path = (int *)malloc(g->V*sizeof(int));
      prizes = (int *)malloc(g->C*sizeof(int));
      if (path == NULL || prizes == NULL) exit(-1);
      for (i=0; i<g->C;i++)
        prizes[i] = 0;
      printf("Input start vertex: ");
      scanf("%s", name);
      src = STsearch(g->stV, name);
      len = simplePath(g, prizes, path, src, 0);
      if (len >= 0) {
        printf("Path found: ");
        for (i=0; i<=len; i++) {
          dst = path[i];
          printf("%s%s", g->nodes[dst].name, i<len ? " - " : "");
        }
        printf("\n\n");
      } else {
        printf("Path doesn't exist!\n");
      }
      free(path);
      free(prizes);
      break;
    case 3:
      prizes = (int *)malloc(g->C*sizeof(int));
      if (prizes == NULL) exit(-1);
      for (i=0; i<g->C;i++)
        prizes[i]=0;
      printf("Input start vertex: ");
      scanf("%s", name);
      src = STsearch(g->stV, name);
      best = bestPath(g, prizes, src, 0, 0, 0);
      printf("Maximum possible score in %d moves is %d\n\n", MAXM, best);
      free(prizes);
      break;
    }
  } while (cmd != 0);

  freeAll(g);

  return 0;
}

GraphPlus read_file(char *fileName) {
  char name[MAXC], name1[MAXC];
  int nV, nE, nC, i, k, src, dst, ew, cat, value, iCat;
  prize_t *p;
  FILE *fin;
  GraphPlus g;

  fin = fopen(fileName, "r");
  if (fin == NULL)
    exit(-1);

  fscanf(fin, "%d%d%d", &nV, &nE, &nC);

  g = (GraphPlus) malloc (sizeof(struct graphPlus));
  if (g == NULL) return NULL;
  g->V = nV;
  g->E = nE;
  g->C = nC;
  g->graph = GRAPHinit(nV);
  if (g->graph == NULL) return NULL;
  g->edges = (Edge *)malloc(nE*sizeof(Edge));
  if (g->edges == NULL) return NULL;
  g->stV = STinit(nV);
  if (g->stV == NULL) return NULL;
  g->stC = STinit(nC);
  if (g->stC == NULL) return NULL;
  g->nodes = (node_t *)malloc(nV*sizeof(node_t));
  if (g->nodes == NULL) return NULL;

  for (i=0; i<nV; i++) {
    fscanf(fin, "%s", name);
    STinsert(g->stV, name, i);
    g->nodes[i].prizeList = NULL;
    g->nodes[i].prizeNum = 0;
    g->nodes[i].visited = 0;
    g->nodes[i].name = strdup(name);
    if (g->nodes[i].name == NULL) return NULL;
  }

  for (k=0; k<nE; k++) {
    fscanf(fin, "%s %s %d", name, name1, &ew);
    src = STsearch(g->stV, name);
    dst = STsearch(g->stV, name1);
    GRAPHinsertE(g->graph, src, dst, ew);
  }

  GRAPHedges(g->edges,g->graph);

  for (i=0; i<nE; i++) {
    if (i==0 || (g->edges[i].v != g->edges[i-1].v)) {
      g->nodes[g->edges[i].v].firstEdge = i;
    }
  }

  iCat=0;
  while (fscanf(fin, "%s %s %d", name, name1, &value) == 3) {
    src = STsearch(g->stV, name);
    cat = STsearch(g->stC, name1);
    if (cat<0)
      cat = STinsert(g->stC, name1, iCat++);
    p = malloc(sizeof *p);
    p->val = value;
    p->cat = cat;
    p->used = 0;
    p->next = g->nodes[src].prizeList;
    g->nodes[src].prizeList = p;
    g->nodes[src].prizeNum++;
  }

  fclose(fin);

  return g;
}

int EDGEcmp(GraphPlus g, Edge e1, Edge e2) {
  if (e1.v != e2.v)
    return strcmp(g->nodes[e1.v].name,g->nodes[e2.v].name);
  return strcmp(g->nodes[e1.w].name,g->nodes[e2.w].name);
}

Edge *EDGEsort(GraphPlus g) {
  int i, j;
  Edge e;
  Edge *edges = (Edge *)malloc(g->E*sizeof(Edge));
  if (edges == NULL) return NULL;

  for (i=0; i<g->E; i++)
    edges[i] = g->edges[i];

  for (i=1; i<g->E; i++) {
    e = edges[i];
    j = i-1;
    while (j>=0 && EDGEcmp(g,e,edges[j])<0) {
      edges[j+1] = edges[j];
      j--;
    }
    edges[j+1] = e;
  }
  return edges;
}

void freeAll(GraphPlus g) {
  int v;
  prize_t *t,*next;
  GRAPHfree(g->graph);
  STfree(g->stV);
  STfree(g->stC);
  free(g->edges);
  for (v=0; v < g->V; v++) {
    free(g->nodes[v].name);
    for (t=g->nodes[v].prizeList; t != NULL; t = next) {
      next = t->next;
      free(t);
    }
  }
  free(g->nodes);
  free(g);
}

int simplePath(GraphPlus g, int *prizes, int *path, int i, int move) {
  int j, dst, len;
  prize_t *p;

  if (g->nodes[i].visited != 0)
    return -1;

  path[move] = i;

  for (p=g->nodes[i].prizeList; p!=NULL; p=p->next)
    prizes[p->cat]++;

  if (allPrizes(prizes, g->C))
    return move;

  g->nodes[i].visited = 1;

  for (j=g->nodes[i].firstEdge; j<g->E && g->edges[j].v==i; j++) {
    dst = g->edges[j].w;
    len = simplePath(g, prizes, path, dst, move+1);
    if (len >= 0) {
      g->nodes[i].visited = 0;
      return len;
    }
  }

  for (p=g->nodes[i].prizeList; p!=NULL; p=p->next)
    prizes[p->cat]--;
  g->nodes[i].visited = 0;

  return -1;
}

int allPrizes(int *prizes, int nC) {
  int i;
  for (i=0; i<nC; i++)
    if (prizes[i] == 0)
      return 0;
  return 1;
}

int bestPath(GraphPlus g, int *prizes, int i, int move, int score, int best) {
  int j, dst, val;
  prize_t *p;

  if ((g->nodes[i].prizeNum + 1) == 0 || score<0 || move>MAXM)
    return best;

  val = score * (1+allPrizes(prizes, g->C));
  best = val > best ? val : best;

  if (g->nodes[i].prizeNum > 0) {
    g->nodes[i].prizeNum--;
    for (p=g->nodes[i].prizeList; p!=NULL; p=p->next) {
      if (p->used == 0) {
        prizes[p->cat]++;
        p->used = 1;
        score += p->val;
        val = score * (1+allPrizes(prizes, g->C));
        best = val > best ? val : best;
        for (j=g->nodes[i].firstEdge; j<g->E && g->edges[j].v==i; j++) {
          dst = g->edges[j].w;
          score += g->edges[j].wt;
          best = bestPath(g, prizes, dst, move+1, score, best);
          score -= g->edges[j].wt;
        }
        g->nodes[i].prizeNum++;
        score -= p->val;
        prizes[p->cat]--;
        p->used = 0;

      }
    }
  } else {
    g->nodes[i].prizeNum--;
    for (j=g->nodes[i].firstEdge; j<g->E && g->edges[j].v==i; j++) {
      dst = g->edges[j].w;
      score += g->edges[j].wt;
      best = bestPath(g, prizes, dst, move+1, score, best);
      score -= g->edges[j].wt;
    }
  }
  g->nodes[i].prizeNum++;

  return best;
}


