#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Queue.h"
#include "BST.h"
#include "Graph.h"
#define MAXC 11

int main(int argc, char **argv) {
  int i, v, numV, val, len, diameter = 0, maxval, maxlen;
  char *name;
  FILE *fin;
  Graph G;
  Edge *path = NULL, *bestPath;

  if (argc != 2)
    exit(-1);

  name = argv[1];
  fin = fopen(name, "r");
  if (fin == NULL)
    exit(-1);

  G = GRAPHload(fin);
  if (G == NULL)
    exit(-1);

  numV = GRAPHnumV(G);

  for (v=0; v<numV; v++) {
    len = GRAPHbfs(G, v);
    if (len > diameter)
      diameter = len;
  }
  printf("Diameter: %d\n\n", diameter);
  bestPath = calloc(numV, sizeof(Edge));
  if ((bestPath == NULL))
    exit(-1);

  maxval = maxlen = 0;

  for (v=0; v<numV; v++) {
    val = len = 0;
    path = GRAPHlongestPath(G, v, &len, &val);
    if (val > maxval) {
      maxlen = len;
      maxval = val;
      for (i=0; i<maxlen; i++) {
        bestPath[i] = path[i];
      }
    }
    free(path);
  }

  printf("Length of maximum-weight simple path: %d\n\n", maxval);
  printf("A maximum-weight simple path: \n");
  for (i=0; i < maxlen; i++)
    printf("(%s - %s) \n", GRAPHsearchByIndex(G, bestPath[i].v), GRAPHsearchByIndex(G, bestPath[i].w));

  fclose(fin);
  free(bestPath);
  GRAPHfree(G);

  return 0;
}
