#include <stdio.h>
#include <stdlib.h>

#include "ST.h"

#include "ST.h"

int main(int argc, char **argv) {
  int i, sel = 0, cont = 1;
  FILE *fin, *fout;
  ST st;
  Key k = NULL;
  Item val;

  if (argc < 3)
    exit(-1);

  fin = fopen(argv[1], "r");
  fout = fopen(argv[2], "w");
  if ((fin == NULL) || (fout == NULL))
    exit(-1);

  while(cont) {
        printf("\nOperations on the Symbol Table\n");
        printf("===================\n");
        printf("\t1.Load from file \n");
        printf("\t2.Store to  file \n");
        printf("\t3.Search         \n");
        printf("\t4.Insert         \n");
        printf("\t5.Delete         \n");
        printf("\t6.Modify         \n");
        printf("\t0.Exit           \n");
        printf("sel: ");
        if(scanf("%d",&sel)<=0) {
            printf("Invalid selection!\n");
            exit(0);
        }
        else {
            switch(sel) {
                case 1:     st = STload(fin);
                            break;
                case 2:     STstore(stdout, st);
                            break;
                case 3:     printf("Insert search key: ");
                            k = KEYscan();
                            i = STsearch(st, k);
                            if (i!=-1)
                              printf("Key found!\n");
                            else
                              printf("Key not found!\n");
                            KEYfree(k);
                            k = NULL;
                            break;
                case 4:     printf("Insert new item: ");
                            val = ITEMscan(stdin);
                            if (val == NULL) exit(-1);
                            STinsert(st, val);
                            break;
                case 5:     printf("Insert key: ");
                            k = KEYscan();
                            if (k == NULL) exit(-1);
                            i = STsearch(st, k);
                            if (i==-1)
                              printf("Key not found!\n");
                            else
                              STdelete(st, k);
                            break;
                case 6:     printf("Insert key: ");
                            k = KEYscan();
                            if (k == NULL) exit(-1);
                            i = STsearch(st, k);
                            if (i==-1)
                              printf("Key not found!\n");
                            else {
                              printf("Input new item:\n");
                              STdelete(st, k);
                              val = ITEMscan(stdin);
                              if (val == NULL) exit(-1);
                              STinsert(st, val);
                            }
                            break;
                case 0:     cont = 0;
                            break;
                default:    printf("Invalid option\n");
            }
        }
  }
  if (k!=NULL)
    KEYfree(k);
  STfree(st);
  fclose(fin);
  fclose(fout);
  return 0;
}
