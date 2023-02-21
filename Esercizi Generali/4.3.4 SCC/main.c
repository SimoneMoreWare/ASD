#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>

#define MAXL 11
#include "ST.h"
#include "Graph.h"

Graph read_file(FILE *fin, ST *tab);

int main(int argc, char **argv) {
  int v, w, max=0, *path, stop=0;
  FILE *fin;
  Graph g = NULL;
  ST tab = NULL;
  char select[MAXL], label1[MAXL], label2[MAXL], *sel;

  if (argc != 2) {
    printf("Use: %s <file_in>\n", argv[0]);
    exit(-1);
  }

  fin = fopen(argv[1], "r");
  if (fin == NULL)
    exit(-1);

  g = read_file(fin, &tab);
  if (g == NULL || tab == NULL)
    exit(-1);

  path = malloc(GRAPHnumV(g)*sizeof(int));
  if (path == NULL)
    exit (-1);

  do {
    printf("\nSelect operation:\n");
    printf("\tA: Maximum-length path from vertex v to vertex w\n");
    printf("\tB: Number of simple paths between vertex v and vertex w\n");
    printf("\tC: Strongly-connected components\n");
    printf("\tD: Turn into strongly connected graph\n");
    printf("\tZ: Exit\n");
    scanf("%s", select);
    for(sel=select;!isalpha(*sel);sel++);
    *sel = toupper(*sel);
    switch(*sel) {
        case 'A': {
          printf("Input source and destination vertices:\n");
          scanf("%s %s", label1, label2);
          v = STsearch(tab, label1);
          w = STsearch(tab, label2);
          if (v < 0 || w < 0)
            printf("Vertices not found...\n");
          else if (v == w ) {
            printf("Same vertex...\n");
          } else {
              v = GRAPHlongestPathVW(g, v, w, &max, path);
              if (max > 0) {
                 printf("Distance %d : ", max);
                 for (v=0; v<=max; v++) {
                   if (v) printf(" > ");
                     printf("%s", STsearchByIndex(tab, path[v]));
                 }
                 printf("\n");
              } else {
                  printf("No path between vertices %s and %s\n", label1, label2); }
            }
          }
          break;
        case 'B': {
          printf("Input source and destination vertices v and w:\n");
          scanf("%s %s", label1, label2);
          v = STsearch(tab, label1);
          w = STsearch(tab, label2);
          if (v < 0 || w < 0)
            printf("Vertices not found...\n");
          else if (v == w ) {
            printf("Same vertex...\n");
          } else {
              v = GRAPHlongestPathVW(g, v, w, &max, path);
              if (v > 0)
                printf("Number of paths: %d\n", v);
              else {
                printf("Nodes not connected by any path\n"); }
            }
          }
          break;
        case 'C':
          printf("Number of SCCs: %d\n", GRAPHscc(g, tab, 1));
          break;
        case 'D':
          GRAPHturn2SCC(g, tab);
          break;
        case 'Z':
          stop = 1;
          break;
        default:
          printf("Invalid selection!\n");
    }
  } while(!stop);

  fclose(fin);
  free(path);
  GRAPHfree(g);
  STfree(tab);

  return 0;
}

Graph read_file(FILE *fin, ST *tab) {
  int id1, id2;
  char label1[MAXL], label2[MAXL];
  Graph G;

  *tab = STinit(1);
  if (*tab == NULL) return NULL;

  while(!feof(fin)) {
    fscanf(fin, "%s %s", label1, label2);
    id1 = STsearch(*tab, label1);
    if (id1 < 0) {
      id1 = STinsert(*tab, label1);
      if (id1 < 0) exit(-1);
    }
    id2 = STsearch(*tab, label2);
    if (id2 < 0) {
      id2 = STinsert(*tab, label2);
      if (id2 < 0) exit(-1);
    }
  }

  rewind(fin);

  G = GRAPHinit(STsize(*tab));
  if (G == NULL) return NULL;

  while(fscanf(fin, "%s %s", label1, label2) == 2) {
    id1 = STsearch(*tab, label1);
    id2 = STsearch(*tab, label2);
    if (id1 >= 0 && id2 >= 0)
      GRAPHinsertE(G, id1, id2);
    }

  return G;
}

