/*
 * >
 *
 * primo punto
 *
 * effettuare visita in profondità, se non ha archi back allora è un dag
 * effettuare powerset per cercare tutti gli archi da rimuovere, in pratica l'insieme degli archi da eliminare sono diversi in base al vertice da dove parti, ma per un vertice qualsiasi si devono comunque eliminare tutti gli archi back per ottenere un dag
 * considerare tutti i possibili insiemi per poter scegliere poi quello di peso massimo

svolgo il powerset per cercare tutte gli archi da rimuovere, per far questo svolgo una visita in profondità del dag e se non incontro archi back la soluzione va bene, in seguito seleziono la soluzione che rimuove il minor numero di archi e con peso maggiore
in teoria ti basta rimuovere dei set di archi , devi trovare il numero minimo di archi che se tolti ti trasformano il grafo in un dag


 */
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#define MAXC 11

int main(void) {
    int i, cont, sel;
    char name[MAXC];
    Graph G;
    FILE *fin, *fout;
    Edge *dagedge;
    int flag_back=0;
    int flag_test6=0;
    int flag_test7=0;
    int cnt=0;
    int countbackedge=0;
    cont = 1;
    while(cont) {
        printf("\nOperations on weighted directed graphs\n");
        printf("===============\n");
        printf("1.Load graph from file\n");
        printf("2.Store graph to file\n");
        printf("3.Edge Min for DAG\n");
        printf("4.Remove EDGE MAX \n");
        printf("5. Longest Path\n");
        printf("6.Free graph and exit\n");
        printf("Enter your choice : ");
        if(scanf("%d",&i)<=0) {
            printf("Integers only!\n");
            exit(0);
        }
        else {
            switch(i) {
                case 1:     printf("Input file name: ");
                    cnt=0;
                    scanf("%s", name);
                    fin = fopen(name, "r");
                    if (fin == NULL)
                        exit(-1);
                    G = GRAPHload(fin);
                    fclose(fin);
                    flag_back=0;
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
                case 3:
                    flag_test6=1;
                    dagedge=malloc(GRAPHfvertexdim(G)*sizeof(Edge));
                    for(i=0;i< GRAPHfvertexdim(G);i++){
                        GRAPHdfs(G,i,&flag_back,&dagedge,&cnt,&countbackedge);
                    }
                    if(flag_back==0) printf("Grafo è gia un DAG");
                    break;
                case 4:
                    if(flag_test6==1){
                        flag_test7=1;
                        if(flag_back!=0) EDGEdag(G,dagedge,cnt,countbackedge);
                    }else{
                        printf("Devi effettuare prima la dfs, premere 6");
                    }
                    break;
                case 5:
                    if(flag_test7==1){
                        DAGrts(G);
                    }else{
                        printf("Devi creare prima il DAG");
                    }
                    break;
                case 6:     cont = 0;
                    break;
                default:    printf("Invalid option\n");
            }
        }
    }
    GRAPHfree(G);
    return 0;
}
