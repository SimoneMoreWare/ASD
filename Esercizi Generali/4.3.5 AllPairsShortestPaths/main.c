#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>
#include "ST.h"
#include "Graph.h"

#define MAXL 31

Graph read_file(FILE *fin, ST *st, char ***tab, int *V);
void generateSetV(Graph g, int **dist, char **tab);

int main(int argc, char **argv) {
  int i, j, V, **dist, *mindist;
  Graph g = NULL;
  ST st = NULL;
  char **tab = NULL;
  FILE *fin;

  if (argc != 2) {
    printf("Use: %s <file_in>\n", argv[0]);
    exit(-1);
  }

  fin = fopen(argv[1], "r");
  if (fin == NULL)
    exit(-1);

  g = read_file(fin, &st, &tab, &V);

  if (g == NULL || st == NULL || tab == NULL)
    exit(-1);

  printf("Floyd-Warshall's algorithm\n");
  dist = GRAPHapspFW(g);
  if (dist == NULL)
    exit(-1);

  for(i=0;i<V;i++) {
    for(j=0;j<V;j++)
      printf("%d\t", dist[i][j]);
    printf("\n");
  }
  system("pause");

  printf("Iterated Dijkstra's algorithm\n");
  for (i=0; i<V; i++) {
    mindist = GRAPHssspD(g, i);
    if (mindist == NULL) exit(-1);
    for(j=0; j<V; j++)
      dist[i][j] = mindist[j];
    free(mindist);
  }

  for(i=0;i<V;i++) {
    for(j=0;j<V;j++)
      printf("%d\t", dist[i][j]);
    printf("\n");
  }
  system("pause");

  generateSetV(g, dist, tab);

  fclose(fin);
  for (i=0; i<V; i++) {
    free(tab[i]);
    free(dist[i]);
  }
  free(dist);
  free(tab);
  STfree(st);
  GRAPHfree(g);

  return 0;
}

Graph read_file(FILE *fin, ST *st, char ***tab, int *V) {
  int i, id1, id2;
  char label1[MAXL], label2[MAXL];
  Graph g;

  fscanf(fin, "%d", V);

  g = GRAPHinit(*V);
  if (g == NULL)
    return NULL;

  *st = STinit(*V);
  if (*st == NULL)
    return NULL;

  *tab = calloc(*V,sizeof(char *));
  if (tab == NULL)
    return NULL;

  for (i=0; i<*V; i++) {
    fscanf(fin, "%s", label1);
    (*tab)[i] = strdup(label1);
    STinsert(*st, (*tab)[i], i);
  }

  while(fscanf(fin, "%s %s %d", label1, label2, &i) == 3) {
    id1 = STsearch(*st, label1);
    id2 = STsearch(*st, label2);
    if (id1 != id2 && id1 >= 0 && id2 >= 0)
      GRAPHinsertE(g, id1, id2, i);
    }
  return g;
}

void combV(Graph g, int k, int n, int *set, int *bestVset, int pos, int start, int *sum, Edge *bestEset, int *eNum, int *stop, int **dist, char **tab) {
  int i;
  int nCC, a = 1;
  int *cc;
  if (pos >= k) {
    printf("Vertices removed from G: {");
    for(i=0;i<k;i++)
      printf("%s%s", i ? ", " : "", tab[set[i]]);
    printf("} ");
    /* Rimozione del set di vertici scelti */
    GRAPHdeleteV(g, set, k);

    /* Verifica di aciclicità e contestuale calcolo delle CC mediante una versione riadattata della DFS */
    cc = GRAPHdfs(g, &nCC, &a);
    printf("number of Connected Components = %d, acyclic = %s\n", nCC, a ? "Y" : "N");

    /* Se aciclico, imposta condizione di stop per set a cardinalità maggiore di questa */
    if (a) {
      *stop = 1;
      if (nCC==1)
        printf("No need for more edges \n");
    }
    else {
      /* il set rimosso attualmente non rende il grafo aciclico, per cui non fare altro lavoro */
      GRAPHreset(g);
      free(cc);
      return;
    }

    /* Riconnessione del grafo (se necessario) */
    GRAPHconnect(g, cc, nCC, sum, bestEset, eNum, dist, tab);

    /* Reset */
    GRAPHreset(g);
    free(cc);
    return;
  }

  for(i=start;i<n;i++) {
    set[pos] = i;
    combV(g, k, n, set, bestVset, pos+1, i+1, sum, bestEset, eNum, stop, dist, tab);
  }
}

void generateSetV(Graph g, int **dist, char **tab) {
  int i, n = GRAPHgetNumV(g), sum = -1, stop = 0, eNum = 0;
  int *set = calloc(n, sizeof(int));
  int *bestVset = calloc(n, sizeof(int));
  Edge *bestEset = calloc(n, sizeof(Edge));
  if (set == NULL || bestVset == NULL || bestEset == NULL)
    exit(-1);
  /*  include il set vuoto e itera fino al massimo a |V|-2 (incluso) */
  for(i=0;(i<n-1) && (stop==0);i++) {
    printf("Set size %d\n", i);
    combV(g, i, n, set, bestVset, 0, 0, &sum, bestEset, &eNum, &stop, dist, tab);
  }
  free(set);
  free(bestVset);
  free(bestEset);
}
