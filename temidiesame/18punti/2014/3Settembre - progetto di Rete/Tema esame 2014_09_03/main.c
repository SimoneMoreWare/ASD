#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main()
{
    Grafo g;
    FILE *f;
    int k=2, m=2;

    f=fopen("grafo.txt", "r");
    if(f==NULL) exit(EXIT_FAILURE);

    g=GRAFOload(f);

    printf("---PROBLEMA DI VERIFICA---\n");
    if(GRAFOverifica(g, k, m)==VERO){
        printf("Soluzione valida.\n\n");
    }
    else
        printf("Soluzione non valida.\n\n");

    GRAFOdeleteArchi(g);

    printf("---PROBLEMA DI RICERCA---\n");
    GRAFOsolve(g, m, k);
    return 0;
}
