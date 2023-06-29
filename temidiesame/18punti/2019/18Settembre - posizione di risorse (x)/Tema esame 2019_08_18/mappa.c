#include "mappa.h"

//funzioni di libreria
static int **malloc2D(int nr, int nc, int value){
    int i, **mat, j;
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
    for(i=0; i<nr; i++){
        for(j=0; j<nc; j++){
            mat[i][j]=value;
        }
    }
    return mat;
}

static void free2D(int **mat, int nr){
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

Ostacolo OSTACOLOcreate(int riga, int colonna){
    Ostacolo o;
    o.riga=riga;
    o.colonna=colonna;
    return o;
}

Mappa MAPPAcreate(int nr, int nc){
    Mappa m;
    m.mat=malloc2D(nr, nc, EMPTY);
    m.nr=nr;
    m.nc=nc;
    m.nOstacoli=0;
    m.ostacoli=(Ostacolo*)malloc((nr*nc)*sizeof(Ostacolo));
    if(m.ostacoli==NULL){
       printf("Errore di allocazione.");
       exit(EXIT_FAILURE);
    }
    return m;
}

Mappa MAPPAread(FILE *f){
    int nr, nc, r, c;
    Mappa m;
    fscanf(f, "%d %d", &nr, &nc);
    m=MAPPAcreate(nr, nc);
    while(fscanf(f, "%d %d", &r, &c)==2){
       m.mat[r][c]=OSTACOLO;
       m.ostacoli[m.nOstacoli]=OSTACOLOcreate(r, c);
       (m.nOstacoli)++;
    }
    return m;
}

void MAPPAclear(Mappa m){
    free2D(m.mat, m.nr);
    if(m.ostacoli!=NULL)
       free(m.ostacoli);
    return;
}
