#include <stdio.h>
#include <stdlib.h>
#include "sinergia.h"

static int **malloc2D(int nr, int nc){
    int **mat;
    int i;

    mat=(int**)malloc(nr*sizeof(int*));
    if(mat==NULL){
        printf("Errore di allocazione.");
        exit(EXIT_FAILURE);
    }

    for(i=0; i<nr; i++){
        mat[i]=(int*)malloc(nc*sizeof(int));
        if(mat[i]==NULL){
            printf("Errore di allocazione.");
            exit(EXIT_FAILURE);
        }
    }
    return mat;
}




static void free2D(int **mat, int nr){
    int i;

    if(mat!=NULL){
        for(i=0; i<nr; i++){
            free(mat[i]);
        }
        free(mat);
    }
    return;
}




Sinergia SINERGIAread(FILE *f, int P){
    Sinergia s;
    int i, j;

    s.S=malloc2D(P, P);
    s.P=P;
    for(i=0; i<P; i++){
        for(j=0; j<P; j++){
            fscanf(f, "%d", &s.S[i][j]);
        }
    }
    return s;
}




void SINERGIAclear(Sinergia s){
    free2D(s.S, s.P);
    return;
}
