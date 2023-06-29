#include <stdio.h>
#include <stdlib.h>
#include "griglia.h"
#include "vincoli.h"

typedef enum{VERO, FALSO}Boolean;

Boolean verifica(Vincoli vRighe, Vincoli vColonne, Griglia proposta);
void copiaColonna(int *vet, int**mat, int nr, int colonna);
Boolean check(Vincolo v, int *vet, int dim);
void solve(Griglia g, Vincoli vRighe, Vincoli vColonne);
Boolean solveR (Griglia *g, Vincoli *vRighe, Vincoli *vColonne, int pos);

int main(){
    Vincoli vRighe, vColonne;
    Griglia g, proposta;
    FILE *fg, *fp;

    fg=fopen("gruppi.txt", "r");
    if(fg==NULL) exit(EXIT_FAILURE);

    vRighe=VINCOLIread(fg);
    vColonne=VINCOLIread(fg);

    g=GRIGLIAcreate(vRighe.dim, vColonne.dim);

    fp=fopen("proposta.txt", "r");
    if(fp==NULL) exit(EXIT_FAILURE);

    proposta=GRIGLIAread(g.nr, g.nc, fp);

    printf("---PROBLEMA DI VERIFICA---\n");
    if(verifica(vRighe, vColonne, proposta)==VERO){
       printf("Soluzione valida.\n\n");
    }
    else
       printf("Soluzione non valida.\n\n");

    printf("---PROBLEMA DI RICERCA---\n");
    solve(g, vRighe, vColonne);
    printf("La soluzione e' stata stampata con successo sul file 'soluzione.txt'\n");

    GRIGLIAclear(g);
    VINCOLIclear(vRighe);
    VINCOLIclear(vColonne);
    GRIGLIAclear(proposta);
    return 0;
}




Boolean verifica(Vincoli vRighe, Vincoli vColonne, Griglia proposta){
   int r, c, *colonna;

   colonna=(int*)malloc(proposta.nr*sizeof(int));
   if(colonna==NULL) exit(EXIT_FAILURE);

   for(r=0; r<proposta.nr; r++)
      if(check(vRighe.vincoli[r], proposta.griglia[r], proposta.nc)==FALSO)
         return FALSO;
   for(c=0; c<proposta.nc; c++){
      copiaColonna(colonna, proposta.griglia, proposta.nr, c);
      if(check(vColonne.vincoli[c], colonna, proposta.nr)==FALSO)
         return FALSO;
   }
   return VERO;
}


void copiaColonna(int *vet, int**mat, int nr, int colonna){
   int i;
   for(i=0; i<nr; i++){
      vet[i]=mat[i][colonna];
   }
   return;
}


Boolean check(Vincolo v, int *vet, int n){
   int i, nGruppi=0, dimG;
   int *dim, maxD=1;

   dim=(int*)malloc(sizeof(int));
   if(dim==NULL) exit(EXIT_FAILURE);

   for(i=0; i<n; i++){
      if(vet[i]==NERO){
         if(i==0 || (i>0 && vet[i-1]==BIANCO)){
            nGruppi++;
            dimG=1;
         }
         else
            dimG++;
         if(i==(n-1)){
            if(maxD==nGruppi){
                maxD=2*maxD;
                dim=realloc(dim, maxD*sizeof(int));
                if(dim==NULL) exit(EXIT_FAILURE);
            }
            dim[nGruppi-1]=dimG;

         }
      }
      else if(i>0 && vet[i]==BIANCO && vet[i-1]==NERO){
         if(maxD==nGruppi){
            maxD=2*maxD;
            dim=realloc(dim, maxD*sizeof(int));
            if(dim==NULL) exit(EXIT_FAILURE);
         }
         dim[nGruppi-1]=dimG;
      }
   }
   if(nGruppi!=v.nGruppi)
      return FALSO;
   for(i=0; i<nGruppi; i++)
      if(dim[i]!=v.dim[i])
         return FALSO;
   return VERO;
}




Boolean rigaHaGruppo(Vincolo vRiga, int indexRiga){
    if(vRiga.nGruppiInseriti==vRiga.nGruppi)
        return FALSO;
    return VERO;
}


void insertGruppoRiga(Griglia g, Vincolo *vRiga, int indexRiga, int indexColonna, int *dimGruppo){
    int i;
    for(i=indexColonna; i<indexColonna+vRiga->dim[vRiga->nGruppiInseriti]; i++){
        g.griglia[indexRiga][i]=NERO;
    }
    (*dimGruppo)=vRiga->dim[vRiga->nGruppiInseriti];
    (vRiga->nGruppiInseriti)++;
    return;
}


void deleteGruppoRiga(Griglia g, Vincolo *vRiga, int indexRiga, int indexColonna){
    int i;
    (vRiga->nGruppiInseriti)--;
    for(i=indexColonna; i<indexColonna+vRiga->dim[vRiga->nGruppiInseriti]; i++){
        g.griglia[indexRiga][i]=BIANCO;
    }
    return;
}


Boolean solveR (Griglia *g, Vincoli *vRighe, Vincoli *vColonne, int pos){
   int r, c, dimGruppo;
   if(pos>=(g->nr*g->nc)){
      return verifica(*vRighe, *vColonne, *g);
   }
   r=pos/(g->nc);
   c=pos%(g->nc);

   if(g->griglia[r][c]==NERO || (c>0 && g->griglia[r][c]==BIANCO && g->griglia[r][c-1]==NERO)){
        if(solveR(g, vRighe, vColonne, pos+1)==VERO)
            return VERO;
        return FALSO;
   }
   if(rigaHaGruppo(vRighe->vincoli[r], r)==VERO && (vRighe->vincoli[r].dim[vRighe->vincoli[r].nGruppiInseriti]+c<=g->nc)){
        insertGruppoRiga(*g, &vRighe->vincoli[r], r, c, &dimGruppo);
        if(solveR(g, vRighe, vColonne, pos+1)==VERO)
            return VERO;
        deleteGruppoRiga(*g, &vRighe->vincoli[r], r, c);
        if(solveR(g, vRighe, vColonne, pos+1)==VERO)
            return VERO;
   }
   else{
        if(solveR(g, vRighe, vColonne, pos+1)==VERO)
            return VERO;
   }
   return FALSO;
}


void solve(Griglia g, Vincoli vRighe, Vincoli vColonne){
   solveR(&g, &vRighe, &vColonne, 0);
   GRIGLIAprint(g, fopen("soluzione.txt", "w"));
   return;
}


