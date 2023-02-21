/*
Questo codice implementa un algoritmo di backtracking per trovare il sottoinsieme di interruttori più piccolo in grado di accendere tutte le lampadine in una matrice di lampadine. La matrice di lampadine rappresenta una serie di interruttori e di lampadine, con valori 1 e 0 che indicano se un interruttore è collegato a una lampadina.

La funzione principale powerset_disposizioniripetute è una funzione ricorsiva che genera tutti i possibili sottoinsiemi degli interruttori e utilizza una funzione helper check per verificare se un dato sottoinsieme di interruttori accende tutte le lampadine. La funzione powerset_disposizioniripetute utilizza una variabile intera pos per tenere traccia della posizione corrente nell'insieme di interruttori e una serie di puntatori (minimo, best, sol) per tenere traccia del sottoinsieme di interruttori ottimale trovato finora e del sottoinsieme corrente che sta esplorando.

La funzione check accetta una matrice di lampadine, il numero di interruttori e di lampadine, e un array sol, che rappresenta un sottoinsieme di interruttori. La funzione utilizza un array di interi "lampadine" inizializzato con tutti i valori a 0 per tenere traccia dello stato di ciascuna lampadina. La funzione quindi itera attraverso ciascuno interruttore presente in sol, e invertire lo stato della lampadina corrispondente nell'array "lampadine" se l'interruttore è connesso a essa (mat[i][j] == 1). Alla fine, verifica se tutte le lampadine sono accese (lampadine[i] == 1) e restituisce 1 se è così, altrimenti 0.

In sintesi il codice implementa un algoritmo che genera tutti i sottoinsiemi possibili degli interruttori e verifica se un dato sottoinsieme accende tutte le lampadine.
*/

#include <stdio.h>
#include <stdlib.h>

void powerset_disposizioniripetute(int mat[4][5],int n,int m,int *minimo,int *best,int *sol,int pos);
int check(int mat[4][5],int n,int m,int *sol);

int main(){
    int n=4;
    int m=5;
    int mat[4][5]={
            {1,1,0,0,1},
            {1,0,1,0,0},
            {0,1,1,1,0},
            {1,0,0,1,0}
    };
    int minimo=m+1;
    int *best = (int *) malloc(n*sizeof(int));
    int *sol = (int *) malloc(n*sizeof(int));
    int pos=0;
    powerset_disposizioniripetute(mat,n,m,&minimo,best,sol,pos);
    printf("Numero interrutori %d\n ",minimo);
    printf("Interrutori: ");
    for(int i=0;i<m;i++) if(best[i]==1) printf("%d ",i);
    return 0;
}

void powerset_disposizioniripetute(int mat[4][5],int n,int m,int *minimo,int *best,int *sol,int pos){
    int i;
    int minpartial;
    if(pos>=n){
        if(check(mat,n,m,sol)){
            minpartial=0;
            for(i=0;i<n;i++) if(sol[i]==1) minpartial++;
            if(minpartial<*minimo){
                *minimo=minpartial;
                for(i=0;i<n;i++) best[i]=sol[i];
            }
        }
        return;
    }
    sol[pos]=0;
    powerset_disposizioniripetute(mat,n,m,minimo,best,sol,pos+1);
    sol[pos]=1;
    powerset_disposizioniripetute(mat,n,m,minimo,best,sol,pos+1);
}

int check(int mat[4][5],int n,int m,int *sol){
    int *lampadine = calloc(m,sizeof(int));
    int i,j;
    for(i=0;i<n;i++){
        if(sol[i]==1){
            for(j=0;j<m;j++){
                if(mat[i][j]==1){
                    if(lampadine[j]==1) lampadine[j]=0;
                    else lampadine[j]=1;
                }
            }
        }
    }
    for(i=0;i<m;i++){
        if(lampadine[i]!=1) {
            free(lampadine);
            return 0;
        }
    }
    free(lampadine);
    return 1;
}
