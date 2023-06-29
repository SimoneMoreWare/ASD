#include "grid.h"
#include <ctype.h>

static char **malloc2D(int nr, int nc){
    char **mat;
    int i;
    mat=(char**)malloc(nr*sizeof(char*));
    if(mat==NULL){
        exit(EXIT_FAILURE);
    }
    for(i=0; i<nr; i++){
        mat[i]=(char*)malloc(nc*sizeof(char));
        if(mat[i]==NULL){
            exit(EXIT_FAILURE);
        }
    }
    return mat;
}

static void free2D(char **mat, int nr){
    int i;
    if(mat!=NULL){
        for(i=0; i<nr; i++){
            if(mat[i]!=NULL)
                free(mat[i]);
        }
        free(mat);
    }
    return;
}

Grid GRIDcrea(int nr, int nc){
    Grid g;
    g.nr=nr;
    g.nc=nc;
    g.griglia=malloc2D(nr, nc);
    return g;
}

Grid GRIDread(FILE *f){
    Grid g;
    int nr, nc, i, j;
    char c;
    fscanf(f, "%d %d%*c", &nr, &nc);
    g=GRIDcrea(nr, nc);
    for(i=0; i<nr; i++){
       for(j=0; j<nc; j++){
          fscanf(f, "%c", &g.griglia[i][j]);
       }
       fscanf(f, "%*c");
    }
    return g;
}

void GRIDclear(Grid g){
    free2D(g.griglia, g.nr);
    return;
}

void GRIDprint(Grid g, FILE *f){
    int i, j;
    for(i=0; i<g.nr; i++){
       for(j=0; j<g.nc; j++){
          fprintf(f, "%c ", g.griglia[i][j]);
       }
       fprintf(f, "\n");
    }
    return;
}
