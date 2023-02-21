#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "PQ.h"

int main(int argc, char *argv[]) {
    int N, sel = 0, cont = 1, i, x, min = 0, q, qcount;
    char fileName[200];
    PQ *pqv;
    FILE *fin, *fout;

    if (argc < 2)
      exit(-1);
    N = atoi(argv[1]);

    pqv = calloc(N, sizeof(*pqv));
    for(i=0; i<N; i++) {
      pqv[i] = PQinit();
      if (pqv[i] == NULL) exit(-1);
    }

    while(cont)  {
        printf("\nOperations on the Priority Queue\n");
        printf("================\n");
        printf("\t1.Display single queue \n");
        printf("\t2.Display all queues   \n");
        printf("\t3.Insert               \n");
        printf("\t4.Insert (automatic)   \n");
        printf("\t5.Extract              \n");
        printf("\t6.Store to file  \n");
        printf("\t7.Load from file \n");
        printf("\t0.Exit           \n");
        printf("sel: ");
        if(scanf("%d",&sel)<=0) {
            printf("Invalid selection!\n");
            exit(0);
        }
        else {
            switch(sel) {
                case 1:     do {
                              printf("Input queue index [0 - %d]: ", N-1);
                              fscanf(stdin, "%d", &x);
                            }
                            while(x < 0 || x >= N);
                            PQstore(stdout, pqv[x]);
                            break;
                case 2:     for(i=0;i<N;i++) {
                              printf(" :: Q%d ::\n", i);
                              PQstore(stdout, pqv[i]);
                            }
                            break;
                case 3:     do {
                              printf("Input queue index [0 - %d]: ", N-1);
                              fscanf(stdin, "%d", &x);
                            }
                            while(x < 0 || x >= N);
                            printf("Insert details prio[int] serv[char*] ccli [char*] \n");
                            PQinsert(pqv[x], ITEMscan(stdin));
                            break;
                case 4:     printf("Insert details prio[int] serv[char*] ccli [char*] \n");
                            for(i=0; i<N; i++)
                              if (PQsize(pqv[i]) < PQsize(pqv[min]))
                                min = i;
                            PQinsert(pqv[min], ITEMscan(stdin));
                            break;
                case 5:     do {
                              printf("Insert queue index [0 - %d]: ", N-1);
                              fscanf(stdin, "%d", &x);
                            }
                            while(x < 0 || x >= N);
                            if (PQempty(pqv[x]))
                                printf("\nEmpty queue!\n");
                            else
                                ITEMstore(stdout, PQextractMax(pqv[x]));
                            break;
                case 6:     printf("Input file name: ");
                            scanf("%s", fileName);
                            fout = fopen(fileName, "w");
                            if (fout != NULL) {
                              for(i=0; i<N; i++) {
                                fprintf(fout,"%d %d\n", i, PQsize(pqv[i]));
                                PQstore(fout, pqv[i]);
                              }
                              fclose(fout);
                            }
                            break;
                case 7:     printf("Input file name: ");
                            scanf("%s", fileName);
                            fin = fopen(fileName, "r");
                            if (fin != NULL) {
                                while(fscanf(fin, "%d %d\n", &q, &qcount) == 2) {
                                  for(i=0; i<qcount; i++)
                                    PQinsert(pqv[q], ITEMscan(fin));
                                }
                              fclose(fin);
                            }
                            break;
                case 0:     cont = 0;
                            for(i=0; i<N; i++)
                              PQfree(pqv[i]);
                            free(pqv);
                            break;
                default:    printf("Invalid option\n");
            }
        }
    }
    return 0;
}
