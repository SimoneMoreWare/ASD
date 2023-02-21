#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#define MAXC 11

int main(void) {
  int i, cont, sel, id1, id2;
  char name[MAXC], label[MAXC];
  Graph G;
  FILE *fin, *fout;

  cont = 1;
  while(cont) {
    printf("\nOperations on unweighted directed graphs\n");
    printf("===============\n");
    printf("1.Load graph from file\n");
    printf("2.Edge insertion\n");
    printf("3.Edge removal\n");
    printf("4.Store graph to file\n");
    printf("5.Depth-first search\n");
    printf("6.Strongly connected components\n");
    printf("7.Free graph and exit\n");
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
            case 2:     printf("Insert first node = ");
                        scanf("%s", label);
                        id1 = GRAPHgetIndex(G, label);
                        printf("Insert second node = ");
                        scanf("%s", label);
                        id2 = GRAPHgetIndex(G, label);
                        GRAPHinsertE(G, id1, id2);
                        break;
            case 3:     printf("Insert first node = ");
                        scanf("%s", label);
                        id1 = GRAPHgetIndex(G, label);
                        printf("Insert second node = ");
                        scanf("%s", label);
                        id2 = GRAPHgetIndex(G, label);
                        GRAPHremoveE(G, id1, id2);
                        break;
            case 4:     printf("File (0) or Screen (1)? ");
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
            case 5:     printf("Insert start node = ");
                        scanf("%s", label);
                        id1 = GRAPHgetIndex(G, label);
                        GRAPHdfs(G, id1);
                        break;
            case 6:     printf("\nThe graph has %d strongly connected component(s)\n", GRAPHscc(G));
                        break;
            case 7:     cont = 0;
                        break;
            default:    printf("Invalid option\n");
          }
        }
    }
    GRAPHfree(G);
    return 0;
}
