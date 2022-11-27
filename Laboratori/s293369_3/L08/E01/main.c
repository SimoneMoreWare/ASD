#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#define MAXC 11

int main() {
    int i, cont, sel;
    char name[MAXC];
    Graph G=NULL;
    FILE *fin, *fout;
    Listaadj adjL=NULL;
    cont = 1;
    int flagaddfile=0;
    int flagaddlist=0;
    while(cont) {
        printf("\nOperations on weighted undirected graphs\n");
        printf("===============\n");
        printf("1.Load graph from file\n");
        printf("2.Store graph to file\n");
        printf("3.Add List\n");
        printf("4.Store list\n");
        printf("5.Check the vertex are adiacent (con matrice di adiacenza)\n");
        printf("6.Check the vertex are adiacent (con lista di adiacenza)\n");
        printf("7.Print sort vertex and edges\n");
        printf("8.Free graph and exit\n");
        printf("Enter your choice : ");
        if(scanf("%d",&i)<=0) {
            printf("Integers only!\n");
            exit(0);
        }
        else {
            switch(i) {
                case 1:
                    flagaddfile=1;
                    printf("Input file name: ");
                    scanf("%s", name);
                    fin = fopen(name, "r");
                    if (fin == NULL)
                        exit(-1);
                    G = GRAPHload(fin);
                    fclose(fin);
                    break;
                case 2:
                    if(flagaddfile==1){
                        printf("File (0) or Screen (1)? ");
                        scanf("%d", &sel);
                        if (sel==0) {
                            printf("Output file name: ");
                            scanf("%s", name);
                            fout = fopen(name, "w");
                            if (fout == NULL)
                                exit(-1);
                            GRAPHstore(G, fout);
                            fclose(fout);
                        }
                        else
                            GRAPHstore(G,stdout);
                    }else{
                        printf("Carica prima il file con il comando 1\n");
                    }

                    break;
                case 3:
                    if(flagaddfile==1){
                        flagaddlist=1;
                        adjL = LISTload(G);
                    }else{
                        printf("Carica prima il file con il comando 1\n");
                    }
                    break;
                case 4:
                    if(flagaddfile==1 && flagaddlist==1) LISTstore(adjL,stdout);
                    if(flagaddfile==0) printf("Carica prima il file con il comando 1\n");
                    if(flagaddlist==0) printf("Aggiungi lista con il comando 3\n");
                    break;
                case 5:
                    if(flagaddfile==1) check_sottografocompleto_matrix(G);
                    else printf("Carica prima il file con il comando 1\n");
                    break;
                case 6:
                    if(flagaddfile==1 && flagaddlist==1) check_sottografocompleto_list(adjL);
                    if(flagaddfile==0) printf("Carica prima il file con il comando 1\n");
                    if(flagaddlist==0) printf("Aggiungi lista con il comando 3\n");
                    break;
                case 7:
                    if(flagaddfile==1) printsortvertex(G);
                    else printf("Carica prima il file con il comando 1\n");
                    break;
                case 8:
                    cont = 0;
                    break;
                default:
                    printf("Invalid option\n");
            }
        }
    }
    GRAPHfree(G);
    exit(0);
}
