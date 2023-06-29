#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#define MAX 200

typedef enum{KCORE, JEDGECONNECTED}Comando;

Comando leggiComando();
Comando stringToComando(char *comando);

int main()
{
    Graph g;
    FILE *f;
    Comando comando;
    int k, j;

    f=fopen("grafo.txt", "r");
    if(f==NULL){
        printf("Errore nell'apertura del file.");
        exit(EXIT_FAILURE);
    }

    g=GRAPHload(f);

    comando=leggiComando();

    switch(comando){
        case KCORE:
            printf("\nInserisci un numero: ");
            scanf("%d", &k);
            if(k<0){
                printf("\nIl numero inserito deve essere positivo.\n");
                break;
            }
            if(GRAPHkCore(g, k)==VERO){
                printf("\nIl %d-core e' composto dai seguenti vertici:\n", k);
                GRAPHverticiKCorePrint(g, stdout);
            }
            else{
                printf("\nNon esiste il %d-core.\n", k);
            }
            break;
        case JEDGECONNECTED:
            printf("\nInserisci un numero: ");
            scanf("%d", &j);
            if(j<1){
                printf("\nIl numero inserito deve essere maggiore o uguale a 1.\n");
                break;
            }
            GRAPHjConnected(g, j);
            break;
        default:
            printf("\nComando errato.\n");
    }
    return 0;
}




Comando leggiComando(){
    char comando[CAR];
    int i;
    char *menu[2]={"'k-core' per determinare il k-core del grafo;",
                   "'j-edge-connected' per verificare se il grafo e' sia j-edge-connected."};
    printf("Scrivi:\n");
    for(i=0; i<2; i++){
        printf("%d) %s\n", i+1, menu[i]);
    }
    printf("Che cosa vuoi fare? ");
    scanf("%s", comando);
    return stringToComando(comando);
}




Comando stringToComando(char *comando){
    if(strcmp(comando, "k-core")==0)
        return KCORE;
    if(strcmp(comando, "j-edge-connected")==0)
        return JEDGECONNECTED;
    return -1;
}
