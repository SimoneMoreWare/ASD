#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main()
{
    Grafo g;
    FILE *f;
    char identificatore[MAX];

    f=fopen("grafo.txt", "r");
    if(f==NULL) exit(EXIT_FAILURE);

    g=GRAPHload(f);

    if(GRAPHisRegular(g)==VERO){
        printf("Il grafo letto dal file e' regolare.\n\n");
    }
    else
       printf("Il grafo letto dal file non e' regolare.\n\n");

    printf("Digita 'fine' se vuoi terminare, il nome di un vertice in caso contrario.\n");
    printf("Che cosa vuoi fare? ");
    gets(identificatore);
    while(strcmp(identificatore, "fine")!=0){
       GRAPHcamminoMassimo(g, identificatore);
       printf("\nDigita 'fine' se vuoi terminare, il nome di un vertice in caso contrario.\n");
       printf("Che cosa vuoi fare? ");
       gets(identificatore);
    }

    GRAPHfree(g);
    return 0;
}
