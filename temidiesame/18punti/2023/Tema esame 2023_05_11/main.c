#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main()
{
    Grafo g;
    FILE *f;

    f=fopen("grafo.txt", "r");
    if(f==NULL) exit(EXIT_FAILURE);

    g=GRAFOload(f);

    printf("---PROBLEMA DI VERIFICA---\n");
    if(GRAFOverifica(g, "proposta_ok.txt")==VERO){
        printf("Soluzione valida.\n\n");
    }
    else{
        printf("Soluzione non valida.\n\n");
    }

    printf("---PROBLEMA DI RICERCA---\n");
    GRAFOsolve(g);
    return 0;
}
