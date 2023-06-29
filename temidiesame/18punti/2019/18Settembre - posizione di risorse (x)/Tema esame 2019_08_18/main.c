#include <stdio.h>
#include <stdlib.h>
#include "mappa.h"
#include "copertura.h"

int main()
{
    Mappa m;
    Copertura proposta;
    FILE *f1, *f2;
    int K, Z;

    f1=fopen("mappa.txt", "r");
    if(f1==NULL)
        exit(EXIT_FAILURE);
    m=MAPPAread(f1);

    f2=fopen("proposta.txt", "r");
    if(f2==NULL)
        exit(EXIT_FAILURE);

    proposta=COPERTURAread(m, f2);

    printf("---PROBLEMA DI VERIFICA:---\n");
    COPERTURAverifica(proposta, m);

    printf("---PROBLEMA DI RICERCA:---\n");
    K=2;
    Z=2;
    COPERTURAsolveZFisso(m, K, Z);
    COPERTURAsolveZVariabile(m, K);


    fclose(f1);
    MAPPAclear(m);
    fclose(f2);
    COPERTURAclear(proposta);
    return 0;
}
