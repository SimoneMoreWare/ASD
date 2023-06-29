#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "divisioni.h"
#include "dipendenti.h"

typedef struct{
   int divisione, mansione;
}Abbinamento;

typedef struct{
   int **compTot, **addTot;
   Abbinamento *abbinamenti;
   int nDiv, nMans, nDip;
}Associazioni;

int **malloc2D(int nr, int nc, int value);
void free2D(int **mat, int nr);
Abbinamento ABBINAMENTOcreate(int div, int mans);
Associazioni ASSOCIAZIONIcreate(int nDiv, int nMans, int nDip);
void ASSOCIAZIONIclear(Associazioni a);
Mansione fromCharToEnum(char mansione);
Associazioni ASSOCIAZIONIread(Dipendenti dip, Divisioni div, FILE *f);
void solve(Dipendenti dip, Divisioni div);
void solveR(Dipendenti dip, Divisioni div, Associazioni *sol, Associazioni *bestSol, float *min, int pos);

int main()
{
    Dipendenti dip;
    Divisioni div;
    Associazioni proposta;
    FILE *f1, *f2, *f3, *f4;

    f1=fopen("dipendenti.txt", "r");
    if(f1==NULL)
        exit(EXIT_FAILURE);

    f2=fopen("divisioni.txt", "r");
    if(f2==NULL)
        exit(EXIT_FAILURE);

    f3=fopen("proposta.txt", "r");
    if(f3==NULL)
        exit(EXIT_FAILURE);

    f4=fopen("output.txt", "w");

    dip=DIPENDENTIread(f1);

    div=DIVISIONIread(f2);

    proposta=ASSOCIAZIONIread(dip, div, f3);

    printf("---PROBLEMA DI VERIFICA:---\n");
    if(DIVISIONIcheck(div, proposta.compTot, proposta.addTot)==VERO){
        printf("Soluzione valida.\n");
        printf("Scostamento medio: %.2f\n\n", DIVISIONIscostamentoMedio(div, proposta.compTot));
    }
    else{
        printf("Soluzione non valida.\n\n");
    }

    printf("---PROBLEMA DI RICERCA:---\n");
    solve(dip, div);
    DIVISIONIprintAssociazioni(div, f4);
    printf("La soluzione ottima e' salvata sul file 'output.txt'.\n");

    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    DIPENDENTIfree(dip);
    DIVISIONIfree(div);
    ASSOCIAZIONIclear(proposta);
    return 0;
}



int **malloc2D(int nr, int nc, int value){
    int **mat;
    int i, j;
    mat=(int**)malloc(nr*sizeof(int*));
    if(mat==NULL){
        exit(EXIT_FAILURE);
    }
    for(i=0; i<nr; i++){
        mat[i]=(int*)malloc(nc*sizeof(int));
        if(mat[i]==NULL){
            exit(EXIT_FAILURE);
        }
    }

    for(i=0; i<nr; i++)
        for(j=0; j<nc; j++)
            mat[i][j]=value;
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



Abbinamento ABBINAMENTOcreate(int div, int mans){
    Abbinamento a;
    a.divisione=div;
    a.mansione=mans;
    return a;
}




Associazioni ASSOCIAZIONIcreate(int nDiv, int nMans, int nDip){
    Associazioni a;
    a.nDiv=nDiv;
    a.nMans=nMans;
    a.nDip=nDip;
    a.compTot=malloc2D(nDiv, nMans, 0);
    a.addTot=malloc2D(nDiv, nMans, 0);
    a.abbinamenti=(Abbinamento*)malloc(nDip*sizeof(Abbinamento));
    if(a.abbinamenti==NULL)
       exit(EXIT_FAILURE);
    return a;
}




void ASSOCIAZIONIclear(Associazioni a){
    free2D(a.compTot, a.nDiv);
    free2D(a.addTot, a.nDiv);
    if(a.abbinamenti!=NULL)
       free(a.abbinamenti);
    return;
}




Mansione fromCharToEnum(char mansione){
    if(mansione=='o')
       return OPERAIO;
    if(mansione=='a')
       return AMMINISTRATIVO;
    if(mansione=='t')
       return TECNICO;
    if(mansione=='i')
       return INFORMATICO;
    return -1;
}




Associazioni ASSOCIAZIONIread(Dipendenti dip, Divisioni div, FILE *f){
    int nDiv, nDip, i, matricola, mansione, divisione, dipendente;
    Associazioni a;
    Dipendente d;
    char sigla[11], tipo;

    nDiv=DIVISIONIsize(div);
    fscanf(f, "%d", &nDip);
    a=ASSOCIAZIONIcreate(nDiv, MANSIONI, nDip);
    for(i=0; i<nDip; i++){
       fscanf(f, "%d %c %s", &matricola, &tipo, sigla);
       mansione=fromCharToEnum(tipo);
       divisione=DIVISIONIsearch(div, sigla);
       dipendente=DIPENDENTIsearch(dip, matricola);
       a.abbinamenti[dipendente]=ABBINAMENTOcreate(divisione, mansione);
       (a.addTot[divisione][mansione])++;
       d=DIPENDENTIgetDipendente(dip, dipendente);
       a.compTot[divisione][mansione]=a.compTot[divisione][mansione]+d.competenze[mansione];
    }
    return a;
}




void solve(Dipendenti dip, Divisioni div){
    Associazioni sol, bestSol;
    int nDiv, nDip, i;
    float min=INT_MAX;
    Divisione dv;
    Dipendente dp;

    nDiv=DIVISIONIsize(div);
    nDip=DIPENDENTIsize(dip);

    sol=ASSOCIAZIONIcreate(nDiv, MANSIONI, nDip);
    bestSol=ASSOCIAZIONIcreate(nDiv, MANSIONI, nDip);

    solveR(dip, div, &sol, &bestSol, &min, 0);

    for(i=0; i<nDip; i++){
       dp=DIPENDENTIgetDipendente(dip, i);
       dv=DIVISIONIgetDivisione(div, bestSol.abbinamenti[i].divisione);
       DIVISIONEinsert(dv, dp, bestSol.abbinamenti[i].mansione);
    }

    printf("Best solution:\n");
    printf("Scostamento medio: %.2f\n", min);

    ASSOCIAZIONIclear(sol);
    ASSOCIAZIONIclear(bestSol);
    return;
}




void solveR(Dipendenti dip, Divisioni div, Associazioni *sol, Associazioni *bestSol, float *min, int pos){
    int divisione, mansione, i;
    Dipendente d;
    float scostamento;

    scostamento=DIVISIONIscostamentoMedio(div, sol->compTot);

    if(pos>=sol->nDip){
       if(DIVISIONIcheck(div, sol->compTot, sol->addTot)==VERO && scostamento < (*min)){
          (*min)=scostamento;
          for(i=0; i<sol->nDip; i++){
             bestSol->abbinamenti[i]=sol->abbinamenti[i];
          }
       }
       return;
    }

    for(divisione=0; divisione<sol->nDiv; divisione++){
       for(mansione=0; mansione<MANSIONI; mansione++){
          sol->abbinamenti[pos]=ABBINAMENTOcreate(divisione, mansione);
          d=DIPENDENTIgetDipendente(dip, pos);
          sol->compTot[divisione][mansione]=sol->compTot[divisione][mansione]+d.competenze[mansione];
          (sol->addTot[divisione][mansione])++;
          solveR(dip, div, sol, bestSol, min, pos+1);
          sol->compTot[divisione][mansione]=sol->compTot[divisione][mansione]-d.competenze[mansione];
          (sol->addTot[divisione][mansione])--;
       }
    }
    return;
}
