#include <stdio.h>
#include <stdlib.h>
#include "persone.h"
#include "incarichi.h"
#include "sinergia.h"

typedef enum{VERO, FALSO}Boolean;

void leggiFile(char *nomeFile, Persone *p, Incarichi *i, Sinergia *s);
int *leggiAssegnazioni(char *nomeFile, int *nAss);
Boolean verifica(Persone p, Incarichi in, Sinergia s, int *assegnazioni, int nAssegnazioni, int *resaTot);
void solve(Persone p, Incarichi in, Sinergia s);
void dispRip(Incarichi in, Persone p, Sinergia s, int *sol, int *bestSol, int *max, int pos);
int min(int a, int b);

int main()
{
    Persone p;
    Incarichi in;
    Sinergia s;
    int resaTot=0;
    int *assegnazioni, nAssegnazioni;

    leggiFile("input.txt", &p, &in, &s);
    assegnazioni=leggiAssegnazioni("assegnazione_ok.txt", &nAssegnazioni);

    if(verifica(p, in, s, assegnazioni, nAssegnazioni, &resaTot)==VERO){
        printf("Soluzione valida. Resa totale: %d", resaTot);
    }
    else{
        printf("Soluzione non valida.");
    }

    solve(p, in, s);

    PERSONEclear(p);
    INCARICHIclear(in);
    SINERGIAclear(s);
    free(assegnazioni);
    return 0;
}




void leggiFile(char *nomeFile, Persone *p, Incarichi *i, Sinergia *s){
    FILE *f=fopen(nomeFile, "r");
    if(f==NULL){
        printf("Errore nell'apertura del file.");
        exit(EXIT_FAILURE);
    }

    *(i)=INCARICHIread(f);
    *(p)=PERSONEread(f);
    *(s)=SINERGIAread(f, p->P);
    return;
}




int *leggiAssegnazioni(char *nomeFile, int *nAss){
    FILE *f=fopen(nomeFile, "r");
    int *assegnazioni, i;

    if(f==NULL){
        printf("Errore nell'apertura del file.");
        exit(EXIT_FAILURE);
    }

    fscanf(f, "%d", nAss);
    assegnazioni=(int*)malloc(*(nAss)*sizeof(int));
    if(assegnazioni==NULL){
        printf("Errore di allocazione.");
        exit(EXIT_FAILURE);
    }

    for(i=0; i<*(nAss); i++)
        fscanf(f, "%d", &assegnazioni[i]);

    return assegnazioni;
}




Boolean verifica(Persone p, Incarichi in, Sinergia s, int *assegnazioni, int nAssegnazioni, int *resaTot){
    int i, resaI, j, prec, incarico;

    if(nAssegnazioni!=p.P)
        return FALSO;

    for(i=0; i<nAssegnazioni; i++){
        if(assegnazioni[i]<0 || assegnazioni[i]>=in.T)
            return FALSO;
    }

    for(i=0; i<in.T; i++){
        incarico=-1;
        prec=-1;
        resaI=0;
        for(j=0; j<p.P; j++){
            if(assegnazioni[j]==i){
                incarico=i;
                if(prec==-1){
                    resaI=resaI+p.E[j];
                }
                else{
                    resaI=resaI+p.E[j]+s.S[prec][j];
                }
                prec=j;
            }
        }
        if(incarico!=-1 && resaI < (float)(in.D[incarico]*75)/100.0)
            return FALSO;
        if(incarico !=-1)
            *(resaTot)= min(resaI, in.D[incarico]) + *(resaTot);
    }
    return VERO;
}




int min(int a, int b){
    if(a<b)
        return a;
    return b;
}




void solve(Persone p, Incarichi in, Sinergia s){
    int *sol, *bestSol, max=0, incarico, i, j;

    sol=(int*)malloc(p.P*sizeof(int));
    if(sol==NULL){
        printf("Errore di allocazione.");
        exit(EXIT_FAILURE);
    }

    bestSol=(int*)malloc(p.P*sizeof(int));
    if(bestSol==NULL){
        printf("Errore di allocazione.");
        exit(EXIT_FAILURE);
    }

    dispRip(in, p, s, sol, bestSol, &max, 0);

    printf("\n\n--BEST SOLUTION--\n");
    for(i=0; i<in.T; i++){
        incarico=-1;
        for(j=0; j<p.P; j++){
            if(bestSol[j]==i){
                incarico=i;
                printf("%d ", j);
            }
        }
        if(incarico!=-1)
            printf("per l'incarico %d\n", incarico);
    }
    printf("Resa totale: %d\n", max);
    free(sol);
    free(bestSol);
    return;
}



void dispRip(Incarichi in, Persone p, Sinergia s, int *sol, int *bestSol, int *max, int pos){
    int resaTot=0, j, i;
    if(pos>=p.P){
        if(verifica(p, in, s, sol, pos, &resaTot)==VERO && resaTot> *(max)){
            *(max)=resaTot;
            for(j=0; j<p.P; j++)
                bestSol[j]=sol[j];
        }
        return;
    }

    for(i=0; i<in.T; i++){
        sol[pos]=i;
        dispRip(in, p, s, sol, bestSol, max, pos+1);
    }
    return;
}
