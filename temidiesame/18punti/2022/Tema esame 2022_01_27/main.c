#include <stdio.h>
#include <stdlib.h>
#include "copertura.h"
#define NOMEFILE "proposta_ok.txt"
#define NOMEFILE1 "proposta_ko_bianco.txt"
#define NOMEFILE2 "proposta_ko_outofbound.txt"
#define NOMEFILE3 "proposta_ko_overlap.txt"

int main()
{
    Griglia g;
    FILE *f, *f1;
    Copertura proposta;
    int nRegioni;

    f=fopen("griglia.txt", "r");
    if(f==NULL){
        printf("Errore nell'apertura del file.");
        exit(EXIT_FAILURE);
    }

    g=GRIGLIAread(f);

    f1=fopen(NOMEFILE, "r");
    if(f1==NULL){
        printf("Errore nell'apertura del file.");
        exit(EXIT_FAILURE);
    }

    proposta=COPERTURAread(f1);

    printf("---PROBLEMA DI VERIFICA:---\n");
    if(COPERTURAcheck(proposta, g, &nRegioni, GRIGLIAareaBianco(g))==VERO){
        printf("Soluzione valida. Numero regioni: %d\n\n\n", nRegioni);
    }
    else{
        printf("Soluzione non valida.\n\n\n");
    }

    GRIGLIAreset(&g);

    printf("---PROBLEMA DI RICERCA:---\n");
    COPERTURAsolve(g);

    fclose(f);
    fclose(f1);
    GRIGLIAclear(g);
    COPERTURAclear(proposta);
    return 0;
}
