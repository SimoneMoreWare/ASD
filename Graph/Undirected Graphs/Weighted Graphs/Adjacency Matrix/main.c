#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#define MAXC 11

int main(void) {
  int i, cont, sel, id;
  char name[MAXC], label[MAXC];
  Graph G;
  FILE *fin, *fout;

  cont = 1;
  while(cont) {
    printf("\nOperations on weighted undirected graphs\n");
    printf("===============\n");
    printf("1.Load graph from file\n");
    printf("2.Store graph to file\n");
    printf("3.MST with Kruskal's algorithm\n");
    printf("4.MST with Prim's algorithm\n");
    printf("5.Free graph and exit\n");
    printf("Enter your choice : ");
    if(scanf("%d",&i)<=0) {
      printf("Integers only!\n");
      exit(0);
    }
    else {
      switch(i) {
            case 1:     printf("Input file name: ");
                        scanf("%s", name);
                        fin = fopen(name, "r");
                        if (fin == NULL)
                          exit(-1);
                        G = GRAPHload(fin);
                        fclose(fin);
                        break;
            case 2:     printf("File (0) or Screen (1)? ");
                        scanf("%d", &sel);
                        if (sel==0) {
                          printf("Input file name: ");
                          scanf("%s", name);
                          fout = fopen(name, "w");
                          if (fout == NULL)
                            exit(-1);
                          GRAPHstore(G, fout);
                          fclose(fout);
                        }
                        else
                          GRAPHstore(G,stdout);
                        break;
            case 3:     GRAPHmstK(G);
                        break;
            case 4:     printf("Insert start node = ");
                        scanf("%s", label);
                        id = GRAPHgetIndex(G, label);
                        GRAPHmstP(G, id);
                        break;
            case 5:     cont = 0;
                        break;
            default:    printf("Invalid option\n");
      }
    }
  }
  GRAPHfree(G);
  return 0;
}
