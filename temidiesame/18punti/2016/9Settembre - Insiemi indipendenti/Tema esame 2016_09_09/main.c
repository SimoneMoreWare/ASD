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
    if(GRAFOverifica(g, "proposta.txt")==VERO){
       printf("L'insieme letto e' un insieme indipendente.\n\n");
    }
    else
       printf("L'insieme di vertici letto non e' un insieme indipendente.\n\n");

    printf("---PROBLEMA DI RICERCA---\n");
    GRAFOsolve(g);

    GRAFOfree(g);
    return 0;
}
