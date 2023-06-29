#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main()
{
    FILE *f;
    Grafo g;

    f=fopen("g.txt", "r");
    if(f==NULL)
        exit(EXIT_FAILURE);

    g=GRAFOload(f);

    printf("---PROBLEMA DI VERIFICA:---\n");
    if(GRAFOcheck(g, "partizione.txt")==VERO){
        printf("Soluzione valida.\n\n");
    }
    else
        printf("Soluzione non valida.\n\n");

    printf("---PROBLEMA DI RICERCA:---\n");
    GRAFOsolve(g);

    GRAFOfree(g);
    fclose(f);
    return 0;
}
