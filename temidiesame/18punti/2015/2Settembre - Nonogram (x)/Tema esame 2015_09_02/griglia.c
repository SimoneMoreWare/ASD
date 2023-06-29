#include "griglia.h"

int **malloc2d(int nr, int nc, int value){
    int **mat;
    int i, j;
    mat=(int**)malloc(nr*sizeof(int*));
    if(mat==NULL) exit(EXIT_FAILURE);
    for(i=0; i<nr; i++){
        mat[i]=(int*)malloc(nc*sizeof(int));
        if(mat[i]==NULL) exit(EXIT_FAILURE);
    }
    for(i=0; i<nr; i++)
        for(j=0; j<nc; j++)
            mat[i][j]=value;
    return mat;
}


void free2d(int **mat, int nr){
    int i;
    if(mat!=NULL){
       for(i=0; i<nr; i++)
            if(mat[i]!=NULL)
                free(mat[i]);
       free(mat);
    }
    return;
}


Griglia GRIGLIAcreate(int nr, int nc){
   Griglia g;
   g.nr=nr;
   g.nc=nc;
   g.griglia=malloc2d(nr, nc, BIANCO);
   return g;
}


Griglia GRIGLIAread(int nr, int nc, FILE *f){
   Griglia g=GRIGLIAcreate(nr, nc);
   int i, j;
   for(i=0; i<nr; i++)
      for(j=0; j<nc; j++)
         fscanf(f, "%d", &g.griglia[i][j]);
   return g;
}


void GRIGLIAprint(Griglia g, FILE *f){
   int i, j;
   for(i=0; i<g.nr; i++){
      for(j=0; j<g.nc; j++)
         fprintf(f, "%d ", g.griglia[i][j]);
      fprintf(f, "\n");
   }
   return;
}


void GRIGLIAclear(Griglia g){
   free2d(g.griglia, g.nr);
   return;
}
