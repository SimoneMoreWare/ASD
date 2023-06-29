#include "copertura.h"
#include "Queue.h"

//STATIC
static int **malloc2D(int nr, int nc, int value);
static void free2D(int **mat, int nr);
static Boolean isMossaValida(int **mat, int nr, int nc, int riga, int colonna, int target);
static Boolean checkRisorse(int **mat, int nr, int nc, Risorsa ris, int target, int maxD);
static void dispRip(Mappa m, Copertura *sol, Copertura *bestSol, int *max, int pos);
static void fillRisorsa(int **mat, int nr, int nc, Risorsa ris, int target, int maxD);
static void deleteRisorsa(int **mat, int nr, int nc, int target);
static int getCover(int **mat, int nr, int nc);
static void print2D(int **mat, int nr, int nc, FILE *f);
static void copia2D(int **mat1, int **mat2, int nr, int nc);



//RISORSA
Risorsa RISORSAcreate(int riga, int colonna){
    Risorsa r;
    r.riga=riga;
    r.colonna=colonna;
    return r;
}


Risorsa RISORSAsetNull(){
     Risorsa r;
     r.riga=-1;
     r.colonna=-1;
     return r;
}


void RISORSAprint(Risorsa r, FILE *f){
    fprintf(f, "(%d, %d)\n", r.riga, r.colonna);
    return;
}



//COPERTURA
Copertura COPERTURAcreate(int nr, int nc, int Z, int k){
    Copertura c;
    c.nr=nr;
    c.nc=nc;
    c.Z=Z;
    c.k=k;
    c.mat=malloc2D(nr, nc, EMPTY);
    c.risorse=(Risorsa*)malloc(Z*sizeof(Risorsa));
    if(c.risorse==NULL){
       printf("Errore di allocazione.");
       exit(EXIT_FAILURE);
    }
    return c;
}


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


Copertura COPERTURAread(Mappa m, FILE *f){
    int distanza, nRisorse, i, r, c, j;
    Copertura cop;
    fscanf(f, "%d %d", &distanza, &nRisorse);
    cop=COPERTURAcreate(m.nr, m.nc, nRisorse, distanza);
    for(i=0; i<nRisorse; i++){
       fscanf(f, "%d %d", &r, &c);
       cop.risorse[i]=RISORSAcreate(r, c);
    }
    for(i=0; i<m.nr; i++){
       for(j=0; j<m.nc; j++){
          fscanf(f, "%d", &cop.mat[i][j]);
       }
    }
    return cop;
}


void COPERTURAprint(Copertura c, FILE *f){
    int i;
    for(i=0; i<c.Z; i++){
        fprintf(f, "Risorsa %d: ", i+1);
        RISORSAprint(c.risorse[i], f);
    }
    print2D(c.mat, c.nr, c.nc, f);
    return;
}


static void print2D(int **mat, int nr, int nc, FILE *f){
    int i, j;
    for(i=0; i<nr; i++){
        for(j=0; j<nc; j++){
            if(mat[i][j]==OSTACOLO){
               fprintf(f, "#\t");
            }
            else{
                fprintf(f, "%d\t", mat[i][j]);
            }
        }
        fprintf(f, "\n");
    }
    return;
}


void COPERTURAverifica(Copertura c, Mappa m){
    int i, **visited;
    Boolean giusto=VERO;

    printf("****SOLUZIONE LETTA DAL FILE (Z = %d, K = %d)****\n", c.Z, c.k);
    COPERTURAprint(c, stdout);

    for(i=0; i<c.Z; i++){
        if(c.mat[c.risorse[i].riga][c.risorse[i].colonna]!=(i+1)){
            giusto=FALSO;
            break;
        }
    }
    if (giusto==FALSO){
        printf("Soluzione non valida. Non e' possibile generare una soluzione valida con tali risorse.\n\n");
        return;
    }

    for(i=0; i<m.nOstacoli; i++){
       if(c.mat[m.ostacoli[i].riga][m.ostacoli[i].colonna]!=EMPTY){
          giusto=FALSO;
          break;
       }
    }

    if(giusto==VERO){

        for(i=0; i<c.Z; i++){
           if(c.mat[c.risorse[i].riga][c.risorse[i].colonna]!=(i+1)){
               giusto=FALSO;
               break;
           }
           if(checkRisorse(c.mat, c.nr, c.nc, c.risorse[i], i+1, c.k)==FALSO){
              giusto=FALSO;
               break;
            }
        }
        if(giusto==VERO){
            printf("Soluzione valida.\n\n");
            return;
        }
    }
    printf("Soluzione non valida. Una possibile soluzione valida con tali risorse e' presente nel file 'corretto.txt'.\n\n");
    copia2D(c.mat, m.mat, m.nr, m.nc);
    for(i=0; i<c.Z; i++){
        fillRisorsa(c.mat, c.nr, c.nc, c.risorse[i], i+1, c.k);
    }
    COPERTURAprint(c, fopen("corretto.txt", "w"));
    return;

}



static void copia2D(int **mat1, int **mat2, int nr, int nc){
    int i, j;
    for(i=0; i<nr; i++){
        for(j=0; j<nc; j++){
            mat1[i][j]=mat2[i][j];
        }
    }
    return;
}


static Boolean checkRisorse(int **mat, int nr, int nc, Risorsa ris, int target, int maxD){
    int MOVIMENTI=4;
    int rShift[4]={-1, 0, 1, 0};
    int cShift[4]={0, -1, 0, 1};
    int i, r, c;
    int **visited=malloc2D(nr, nc, 0);
    Q q;
    Mossa start, step, m;

    q = QUEUEinit();
    start=MOSSAcreate(ris.riga, ris.colonna, target, 0);
    QUEUEput(q, start);
    visited[start.r][start.c]=1;

    while (!QUEUEempty(q)) {
        m= QUEUEget(q);
        for (i = 0; i < MOVIMENTI; i++) {
            r = m.r + rShift[i];
            c = m.c + cShift[i];
            if (isMossaValida(mat, nr, nc, r, c, target)==VERO && visited[r][c]==0 && (m.dist +1)<=maxD) {
                step=MOSSAcreate(r, c, target, m.dist+1);
                QUEUEput(q, step);
                visited[r][c]=1;
            }
            else if (isMossaValida(mat, nr, nc, r, c, target)==VERO && mat[r][c]==target && visited[r][c]==0 && (m.dist +1) > maxD) {
                return FALSO;
          }
          else if(r>=0 && r<nr && c >=0 && c <nc && mat[r][c]!=target && mat[r][c]!=OSTACOLO && (m.dist +1)<=maxD){
            return FALSO;
          }
        }
      }
    QUEUEfree(q);
    return VERO;
}


static Boolean isMossaValida(int **mat, int nr, int nc, int riga, int colonna, int target){
    if(riga<0 || riga>=nr || colonna <0 || colonna >=nc || mat[riga][colonna]!=target){
          return FALSO;
    }
    return VERO;
}


void COPERTURAsolveZFisso(Mappa m, int K, int Z){
    Copertura sol, bestSol;
    int max=0;

    sol=COPERTURAcreate(m.nr, m.nc, Z, K);
    bestSol=COPERTURAcreate(m.nr, m.nc, Z, K);

    dispRip(m, &sol, &bestSol, &max, 0);

    printf("****GENERAZIONE A Z FISSO (Z = %d, K = %d)****\n", Z, K);
    COPERTURAprint(bestSol, stdout);
    printf("Soluzione con copertura pari a %d.\n\n", max);
    return;
}


static void dispRip(Mappa m, Copertura *sol, Copertura *bestSol, int *max, int pos){
    int i, cover, riga, colonna;

    if(pos>=sol->Z){
        cover=getCover(m.mat, m.nr, m.nc);
        if(cover > *(max)){
            (*max)=cover;
            bestSol->Z=sol->Z;
            for(i=0; i<sol->Z; i++){
                bestSol->risorse[i]=sol->risorse[i];
            }
            copia2D(bestSol->mat, m.mat, m.nr, m.nc);
        }
        return;
    }

    for(riga=0; riga<m.nr; riga++){
        for(colonna=0; colonna<m.nc; colonna++){
            if(m.mat[riga][colonna]!=EMPTY)
                continue;
            sol->risorse[pos]=RISORSAcreate(riga, colonna);
            fillRisorsa(m.mat, m.nr, m.nc, sol->risorse[pos], pos+1, sol->k);
            if(checkRisorse(m.mat, m.nr, m.nc, sol->risorse[pos], pos+1, sol->k)==VERO){
                dispRip(m, sol, bestSol, max, pos+1);
            }
            deleteRisorsa(m.mat, m.nr, m.nc, pos+1);
        }
    }
    return;
}


static void fillRisorsa(int **mat, int nr, int nc, Risorsa ris, int target, int maxD){
    int MOVIMENTI=4;
    int rShift[4]={-1, 0, 1, 0};
    int cShift[4]={0, -1, 0, 1};
    int i, r, c;
    Q q;
    Mossa start, step, m;

    q = QUEUEinit();
    start=MOSSAcreate(ris.riga, ris.colonna, target, 0);
    QUEUEput(q, start);

    while (!QUEUEempty(q)) {
        m= QUEUEget(q);
        for (i = 0; i < MOVIMENTI; i++) {
            r = m.r + rShift[i];
            c = m.c + cShift[i];
            if (isMossaValida(mat, nr, nc, r, c, EMPTY)==VERO && (m.dist +1)<=maxD) {
                step=MOSSAcreate(r, c, target, m.dist+1);
                QUEUEput(q, step);
                mat[r][c]=target;
            }
        }
    }
    QUEUEfree(q);
    return;
}


static void deleteRisorsa(int **mat, int nr, int nc, int target){
    int i, j;
    for(i=0; i<nr; i++){
        for(j=0; j<nc; j++){
            if(mat[i][j]==target){
                mat[i][j]=EMPTY;
            }
        }
    }
    return;
}


static int getCover(int **mat, int nr, int nc){
    int i, j, count=0;
    for(i=0; i<nr; i++){
        for(j=0; j<nc; j++){
            if(mat[i][j]!=EMPTY && mat[i][j]!=OSTACOLO){
                count++;
            }
        }
    }
    return count;
}


void COPERTURAsolveZVariabile(Mappa m, int K){
    Copertura sol, bestSol;
    int bestCover=0, coverMax=0, bestRisorse;
    int Z;

    sol=COPERTURAcreate(m.nr, m.nc, m.nr*m.nc, K);
    bestSol=COPERTURAcreate(m.nr, m.nc, m.nr*m.nc, K);

    for(Z=1; Z<=m.nr*m.nc; Z++){
        sol.Z=Z;
        dispRip(m, &sol, &bestSol, &coverMax, 0);
        if(coverMax>bestCover){
            bestCover=coverMax;
            bestRisorse=Z;
        }
        else if(coverMax==bestCover){
            break;
        }
    }

    printf("****GENERAZIONE A Z VARIABILE (K = %d)****\n", K);
    COPERTURAprint(bestSol, stdout);
    printf("Soluzione con copertura pari a %d con %d risorse.\n\n", bestCover, bestRisorse);
    return;
}


void COPERTURAclear(Copertura c){
    free2D(c.mat, c.nr);
    if(c.risorse!=NULL)
       free(c.risorse);
    return;
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
