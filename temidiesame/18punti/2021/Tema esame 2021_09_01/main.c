#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main()
{
    FILE *f;
    Graph g;

    f=fopen("grafo.txt", "r");
    if(f==NULL) exit(EXIT_FAILURE);

    g=GRAPHload(f);

    fclose(f);

    f=fopen("verifica.txt", "r");
    if(f==NULL) exit(EXIT_FAILURE);

    printf("---PROBLEMA DI VERIFICA:---\n");
    if(GRAPHverifica(g, f)==VERO){
        printf("Il file letto contiene un ciclo.\n");
    }
    else{
        printf("Il file letto non contiene un ciclo.\n");
    }

    fclose(f);

    printf("\n---PROBLEMA DI RICERCA:---\n");
    GRAPHsolve(g);

    GRAPHfree(g);
    return 0;
}
