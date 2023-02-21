#include <stdio.h>
#include <stdlib.h>

#include "ST.h"

int main(int argc, char **argv) {
  int i, sel = 0, cont = 1;
  FILE *fin;
  ST st = NULL;
  Key k = NULL;

  if (argc < 2)
    exit(-1);

  fin = fopen(argv[1], "r");
  if (fin == NULL)
    exit(-1);

  while(cont) {
        printf("\nOperations on the Symbol Table\n");
        printf("===================\n");
        printf("\t1.Load from file \n");
        printf("\t2.Search         \n");
        printf("\t0.Exit           \n");
        printf("sel: ");
        if(scanf("%d",&sel)<=0) {
            printf("Invalid selection!\n");
            exit(0);
        }
        else {
            switch(sel) {
                case 1:     st = STload(fin);
                            if (st == NULL) exit(-1);
                            break;
                case 2:     printf("Insert search key: ");
                            k = KEYscan();
                            if (k == NULL) {
                              printf("Key not allocated\n");
                              exit(-1);
                            }
                            i = STsearch(st, k);
                            if (i!=-1)
                              printf("Key found at index %d\n", i);
                            else
                              printf("Key not found!\n");
                            KEYfree(k);
                            k = NULL;
                            break;
                case 0:     cont = 0;
                            STfree(st);
                            break;
                default:    printf("Invalid option\n");
            }
        }
  }
  if (k!=NULL)
    KEYfree(k);
  fclose(fin);
  return 0;
}
