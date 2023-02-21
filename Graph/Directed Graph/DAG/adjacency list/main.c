#include <stdio.h>
#include <stdlib.h>
#include "Dag.h"
#define MAXC 21

int main(void) {
  int i, cont, sel, id1, id2;
  char name[MAXC], label[MAXC];
  Dag D;
  FILE *fin, *fout;

  cont = 1;
  while(cont) {
      printf("\nOperations on DAGs\n");
      printf("===============\n");
      printf("1.Load graph from file\n");
      printf("2.Edge insertion\n");
      printf("3.Edge removal\n");
      printf("4.Store graph to file\n");
      printf("5.Reverse topological sort\n");
      printf("6.Free graph and exit\n");
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
                        D = DAGload(fin);
                        fclose(fin);
                        break;
            case 2:     printf("Insert first node = ");
                        scanf("%s", label);
                        id1 = DAGgetIndex(D, label);
                        printf("Insert second node = ");
                        scanf("%s", label);
                        id2 = DAGgetIndex(D, label);
                        DAGinsertE(D, id1, id2);
                        break;
            case 3:     printf("Insert first node = ");
                        scanf("%s", label);
                        id1 = DAGgetIndex(D, label);
                        printf("Insert second node = ");
                        scanf("%s", label);
                        id2 = DAGgetIndex(D, label);
                        DAGremoveE(D, id1, id2);
                        break;
            case 4:     printf("File (0) or Screen (1)? ");
                        scanf("%d", &sel);
                        if (sel==0) {
                          printf("Input file name: ");
                          scanf("%s", name);
                          fout = fopen(name, "w");
                          if (fout == NULL)
                            exit(-1);
                          DAGstore(D, fout);
                          fclose(fout);
                        }
                        else
                          DAGstore(D,stdout);
                        break;
            case 5:     DAGrts(D);
                        break;
            case 6:     cont = 0;
                        break;
            default:    printf("Invalid option\n");
          }
        }
  }
  DAGfree(D);
  return 0;
}
