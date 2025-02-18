#include <stdio.h>
#include <stdlib.h>
#include "percorso.h"

int main()
{
    Griglia g;
    Percorso proposta;
    FILE *f, *f1;
    int cambi;

    f=fopen("griglia.txt", "r");
    if(f==NULL){
        printf("Errore di apertura del file.");
        exit(EXIT_FAILURE);
    }

    g=GRIGLIAread(f);

    f1=fopen("proposta.txt", "r");
    if(f1==NULL){
        printf("Errore di apertura del file.");
        exit(EXIT_FAILURE);
    }

    proposta=PERCORSOread(f1);

    printf("---PROBLEMA DI VERIFICA:---\n");
    if(PERCORSOcheck(proposta, g, &cambi, GRIGLIAareaBianchi(g))==VERO){
        printf("Soluzione valida. Numero cambi di direzione: %d\n\n\n", cambi);
    }
    else{
        printf("Soluzione non valida.\n\n\n");
    }

    printf("---PROBLEMA DI VERIFICA:---\n");
    PERCORSOsolve(g);

    fclose(f);
    fclose(f1);
    GRIGLIAclear(g);
    PERCORSOclear(proposta);
    return 0;
}
