#include <stdio.h>
#include <stdlib.h>
#include "incarichi.h"

Incarichi INCARICHIread(FILE *f){
    Incarichi i;
    int index;

    fscanf(f, "%d", &i.T);
    i.D=(int*)malloc(i.T*sizeof(int));
    if(i.D==NULL){
        printf("Errore di allocazione.");
        exit(EXIT_FAILURE);
    }
    for(index=0; index<i.T; index++)
        fscanf(f, "%d", &i.D[index]);
    return i;
}



void INCARICHIclear(Incarichi i){
    if(i.D!=NULL)
        free(i.D);
    return;
}
