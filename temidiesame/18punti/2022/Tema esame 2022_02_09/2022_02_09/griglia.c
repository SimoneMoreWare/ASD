#include "griglia.h"

/* 
    Alloca la matrice bidimensionale 
    
    Se la definizione, a ogni punto,
    non è andata a buon fine, allora
    esci con fallimento 
*/
static int **malloc2D(int nr, int nc) {
    int **mat, i;
    mat=(int**)malloc(nr*sizeof(int*));
    if(mat==NULL)
        exit(EXIT_FAILURE);
    for(i=0; i<nr; i++){
        mat[i]=(int*)malloc(nc*sizeof(int));
        if(mat[i]==NULL)
            exit(EXIT_FAILURE);
    }
    return mat;
}

/* 
    Dealloca la matrice bidimensionale
*/
static void free2D(int **mat, int nr) {
    int i;
    if(mat!=NULL){
        for(i=0; i<nr; i++){
            if(mat[i]!=NULL){
                free(mat[i]);
            }
        }
        free(mat);
    }
}

/* 
    Inizializza la griglia
*/
Griglia GRIGLIAinit(int nr, int nc) {
    Griglia g;
    g.nr=nr;
    g.nc=nc;
    g.griglia=malloc2D(nr, nc);
    return g;
}

/*
    Legge una griglia da file
*/
Griglia GRIGLIAread(FILE *f) {
    Griglia g;
    int nr, nc, i, j;
    fscanf(f, "%d %d", &nr, &nc);
    g=GRIGLIAinit(nr, nc);
    for(i=0; i<nr; i++)
       for(j=0; j<nc; j++)
          fscanf(f, "%d", &g.griglia[i][j]);
    return g;
}

/*
    Definisce quante caselle bianche ci sono,
    definendo l'area effettiva della griglia
*/
int GRIGLIAareaBianchi(Griglia g) {
    int i, j;
    int area=0;
    for(i=0; i<g.nr; i++)
        for(j=0; j<g.nc; j++)
            if(g.griglia[i][j]==BIANCO)
                area++;
    return area;
}

/*
    Dealloca la griglia
*/
void GRIGLIAclear(Griglia g) {
    free2D(g.griglia, g.nr);
    return;
}
