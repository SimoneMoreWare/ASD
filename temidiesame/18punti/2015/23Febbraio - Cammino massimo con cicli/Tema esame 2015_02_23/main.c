#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main()
{
    Grafo g;
    FILE *f;
    char sorgente[MAX]="A0", destinazione[MAX]="fF";
    int k, p;

    f=fopen("grafo.txt", "r");
    if(f==NULL) exit(EXIT_FAILURE);

    g=GRAFOload(f);

    GRAFOintersezioneEStampaSottocammini(g, "cammini.txt", stdout);

    k=1;
    p=1;
    GRAFOsolve(g, k, p, sorgente, destinazione);
    printf("\n");

    k=6;
    p=7;
    GRAFOsolve(g, k, p, sorgente, destinazione);
    printf("\n");

    GRAFOfree(g);
    return 0;
}
