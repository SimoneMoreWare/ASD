#include "schema.h"

static int **malloc2D(int nr, int nc){
    int **mat, i;
    mat=malloc(nr*sizeof(int**));
    if(mat==NULL) exit(EXIT_FAILURE);
    for(i=0; i<nr; i++){
        mat[i]=(int*)malloc(nc*sizeof(int));
        if(mat[i]==NULL) exit(EXIT_FAILURE);
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

Schema SCHEMAread(FILE *f){
       Schema s;
       int nr, nc, i, j;
       fscanf(f, "%d %d", &nr, &nc);
       s.nr=nr;
       s.nc=nc;
       s.mat=malloc2D(nr, nc);
       for(i=0; i<nr; i++)
          for(j=0; j<nc; j++)
             fscanf(f, "%d", &s.mat[i][j]);
       return s;
}

void SCHEMAprint(Schema s, FILE *f){
       int i, j;
       for(i=0; i<s.nr; i++){
          for(j=0; j<s.nc; j++){
             fprintf(f, "%d ", s.mat[i][j]);
          }
          fprintf(f, "\n");
       }
       return;
}

void SCHEMAclear(Schema s){
       if(s.mat!=NULL)
          free2D(s.mat, s.nr);
       return;
}
