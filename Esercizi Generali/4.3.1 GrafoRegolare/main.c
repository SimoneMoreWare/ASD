#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#define MAXC 21

int main(int argc, char **argv) {
  int id;
  char *name, label[MAXC];
  FILE *fin;
  Graph G;

  if (argc != 2)
    exit(-1);

  name = argv[1];
  fin = fopen(name, "r");
  if (fin == NULL)
    exit(-1);

  G = GRAPHload(fin);
  if (G == NULL) exit(-1);

  if (GRAPHregular(G))
    printf("The graph is regular\n");
  else
    printf("The graph is NOT regular\n");

  while(1) {
    fprintf(stdout, "\nInsert vertex name [fine to quit] > ");
    fscanf(stdin, "%s", label);
    if (!strcmp(label, "fine"))
      break;

    id = GRAPHsearchByKey(G, label);
    if (id == -1) {
      fprintf(stdout, "Invalid selection\n");
      continue;
    }
    GRAPHlongestPath(G, id);
  }

  fclose(fin);
  GRAPHfree(G);

  return 0;
}
