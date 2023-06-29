#include "griglia.h"

//funzioni di libreria
int **malloc2D(int nr, int nc){
    int i, **mat;
    mat=(int**)malloc(nr*sizeof(int));
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


void free2D(int **mat, int nr){
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


Griglia GRIGLIAinit(int nr, int nc){
    Griglia g;
    g.nr=nr;
    g.nc=nc;
    g.griglia=malloc2D(nr, nc);
    return g;
}


Griglia GRIGLIAread(FILE *f){
    int i, nr, nc, j;
    Griglia g;
    fscanf(f, "%d %d", &nr, &nc);
    g=GRIGLIAinit(nr, nc);
    for(i=0; i<nr; i++)
       for(j=0; j<nc; j++)
          fscanf(f, "%d", &g.griglia[i][j]);
    return g;

}


void GRIGLIAfillRegione (Griglia *g, int rI, int cI, int base, int altezza, int value){
    int i, j;
    for(i=rI; i<rI+altezza && i<g->nr; i++)
       for(j=cI; j<cI+base && j<g->nc; j++)
          g->griglia[i][j]=value;
    return;
}


void GRIGLIAdeleteRegione (Griglia *g, int rI, int cI, int base, int altezza){
    int i, j;
    for(i=rI; i<rI+altezza && i<g->nr; i++)
       for(j=cI; j<cI+base && j<g->nc; j++)
          g->griglia[i][j]=BIANCO;
    return;
}


Boolean GRIGLIAcheckRegione(Griglia g, int rI, int cI, int base, int altezza){
    int i, j;
    for(i=rI; i<rI+altezza && i<g.nr; i++)
       for(j=cI; j<cI+base && j<g.nc; j++)
          if(g.griglia[i][j]!=BIANCO)
             return FALSO;
    return VERO;
}


int GRIGLIAareaBianco(Griglia g){
    int i, j, bianco=0;
    for(i=0; i<g.nr; i++)
       for(j=0; j<g.nc; j++)
          if(g.griglia[i][j]!=NERO)
             bianco++;
    return bianco;
}


void GRIGLIAreset(Griglia *g){
    int i, j;
    for(i=0; i<g->nr; i++)
       for(j=0; j<g->nc; j++)
          if(g->griglia[i][j]!=NERO && g->griglia[i][j]!=BIANCO)
             g->griglia[i][j]=BIANCO;
    return;
}


static int minimo(int a, int b){
    if(a<b)
       return a;
    return b;
}


int GRIGLIAgetMaxAreaBianco(Griglia g, int rI, int cI){
   int i, j, base, altezza;

   i=rI;
   altezza=0;
   while(i<g.nr && g.griglia[i][cI]==BIANCO){
      altezza++;
      i++;
   }

   j=cI;
   base=0;
   while(j<g.nc && g.griglia[rI][j]==BIANCO){
      base++;
      j++;
   }


   return minimo(base, altezza);
}


void GRIGLIAclear(Griglia g){
    free2D(g.griglia, g.nr);
    return;
}
