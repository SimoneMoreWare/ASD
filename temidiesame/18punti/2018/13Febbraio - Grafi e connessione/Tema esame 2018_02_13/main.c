#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main()
{
    Grafo g;
    FILE *f;
    Edge *proposta;
    int dim, diametro;

    f=fopen("grafo.txt", "r");
    if(f==NULL)
        exit(EXIT_FAILURE);

    g=GRAFOload(f);

    proposta=GRAFOreadProposta(g, "sol2.txt", &dim);


    printf("---PROBLEMA DI VERIFICA:---\n");
    GRAFOcheckProposte(g, "sol1.txt", "sol2.txt");

    printf("---PROBLEMA DI RICERCA:---\n");
    GRAFOsolve(g);

    GRAFOfree(g);
    return 0;
}
