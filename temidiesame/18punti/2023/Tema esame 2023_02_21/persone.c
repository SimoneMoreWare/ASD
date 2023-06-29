#include <stdio.h>
#include <stdlib.h>
#include "persone.h"

Persone PERSONEread(FILE *f){
    Persone p;
    int index;

    fscanf(f, "%d", &p.P);
    p.E=(int*)malloc(p.P*sizeof(int));
    if(p.E==NULL){
        printf("Errore di allocazione.");
        exit(EXIT_FAILURE);
    }
    for(index=0; index<p.P; index++)
        fscanf(f, "%d", &p.E[index]);
    return p;
}



void PERSONEclear(Persone p){
    if(p.E!=NULL)
        free(p.E);
    return;
}
