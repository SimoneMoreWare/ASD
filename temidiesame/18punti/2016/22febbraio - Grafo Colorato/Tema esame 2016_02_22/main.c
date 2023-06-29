#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main()
{
    FILE *f;
    Grafo g;

    f=fopen("grafo.txt", "r");
    if(f==NULL) exit(EXIT_FAILURE);

    g=GRAFOload(f);
    if(g!=NULL){
        printf("---CAMMINO SEMPLICE A PESO MASSIMO---\n");
        GRAFOcamminoPesoMax(g);
        printf("\n\n");

        printf("---SOTTOGRAFO A PESO MASSIMO---\n");
        GRAFOsottoGrafo(g);
        printf("\n");

    }
    GRAFOfree(g);
    return 0;
}
