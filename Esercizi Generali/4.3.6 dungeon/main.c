#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
#include "Graph.h"
#define MAXC 21

int main() {
  FILE *fin;
  Graph g;
  char name[MAXC];

  printf("Input nome file: ");
  scanf("%s", name);
  fin = fopen(name, "r");
  if (fin == NULL)
    exit(-1);

  g = GRAPHload(fin);
  if (g == NULL)
    exit(-1);

  GRAPHpath(g);

  GRAPHfree(g); 
  fclose(fin);

  return 0;
}
