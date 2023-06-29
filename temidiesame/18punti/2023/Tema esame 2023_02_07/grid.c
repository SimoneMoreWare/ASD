#include "grid.h"

Token **malloc2d(int nr, int nc){
    Token **mat;
    int i;
    mat=(Token**)malloc(nr*sizeof(Token*));
    if(mat==NULL) exit(EXIT_FAILURE);
    for(i=0; i<nr; i++){
       mat[i]=(Token*)malloc(nc*sizeof(Token));
       if(mat[i]==NULL) exit(EXIT_FAILURE);
    }
    return mat;
}


void free2d(Token **mat, int nr){
    int i;
    if(mat!=NULL){
       for(i=0; i<nr; i++){
          if(mat[i]!=NULL)
             free(mat[i]);
       }
       free(mat);
    }
}


Grid GRIDread(FILE *f){
   Grid g;
   int i, j;
   fscanf(f, "%d", &g.nr);
   g.nc=g.nr;
   g.grid=malloc2d(g.nr, g.nc);
   for(i=0; i<g.nr; i++)
      for(j=0; j<g.nc; j++)
         g.grid[i][j]=TOKENread(f);
   return g;
}


void GRIDclear(Grid *g){
   free2d(g->grid, g->nr);
   return;
}

