#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#define M 5
#define PF 10

int main()
{
    Graph g;
    Path proposta, best;
    FILE *f;

    f=fopen("dungeon.txt", "r");
    if(f==NULL){
        printf("Errore nell'apertura del file.");
        exit(EXIT_FAILURE);
    }

    g=GRAPHload(f);
    fclose(f);

    f=fopen("path.txt", "r");
    if(f==NULL){
        printf("Errore nell'apertura del file.");
        exit(EXIT_FAILURE);
    }

    proposta=GRAPHpathLoad(g, f);
    fclose(f);

    printf("~~~LABIRINTO (%d MOSSE e %d PUNTI FERITA):~~~\n", M, PF);
    printf("---PROBLEMA DI VERIFICA:---\n");
    if(GRAPHpathCheck(g, &proposta, M, PF)==VERO){
        printf("Soluzione valida.\n\n\n");
    }
    else{
        printf("Soluzione non valida.\n\n\n");
    }

    printf("---PROBLEMA DI RICERCA:---\n");
    best=GRAPHpathBest(g, M, PF);
    printf("Best solution:\n\n");
    PATHprint(g, best, stdout);
    printf("\n");

    GRAPHfree(g);
    PATHclear(proposta);
    PATHclear(best);
    return 0;
}
