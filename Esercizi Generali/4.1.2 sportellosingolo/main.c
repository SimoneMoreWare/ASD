#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "PQ.h"

int main(int argc, char *argv[]) {
  int sel = 0, cont = 1;
  char fileName[200];
  FILE *fin, *fout;

  PQinit();
  while(cont) {
        printf("\nOperations on the Priority Queue\n");
        printf("===================\n");
        printf("\t1.Display        \n");
        printf("\t2.Insert         \n");
        printf("\t3.Extract        \n");
        printf("\t4.Store to file  \n");
        printf("\t5.Load from file \n");
        printf("\t0.Exit           \n");
        printf("sel: ");
        if(scanf("%d",&sel)<=0) {
            printf("Invalid selection!\n");
            exit(0);
        }
        else {
            switch(sel) {
                case 1:     PQstore(stdout);
                            break;
                case 2:     printf("Insert details prio[int] serv[char*] ccli [char*] \n");
                            PQinsert(ITEMscan(stdin));
                            break;
                case 3:     if (PQempty())
                                printf("\nEmpty Priority Queue!\n");
                            else
                                ITEMstore(stdout, PQextractMax());
                            break;
                case 4:     printf("Input file name: ");
                            scanf("%s", fileName);
                            fout = fopen(fileName, "w");
                            if (fout != NULL) {
                              PQstore(fout);
                              fclose(fout);
                            }
                            break;
                case 5:     printf("Input file name: ");
                            scanf("%s", fileName);
                            fin = fopen(fileName, "r");
                            if (fin != NULL) {
                              PQload(fin);
                              fclose(fin);
                            }
                            break;
                case 0:     cont = 0;
                            PQfree();
                            break;
                default:    printf("Invalid option\n");
            }
        }
    }
    return 0;
}
