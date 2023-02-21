/*
 * intervallo aperto li,hi
 * li estremo inferiore
 * hi estremo superiore
 * durata di = hi - li
 *
 * estremi e durata sono interi
 *
 * si ha collezione di intervalli S
 * memorizzata in un vettore V di N struct interv
 *
 * due intervalli sono incompatibili se
 * li < hj && lj < hi
 *
 * scrivere funzione wrapper e una ricorsiva
 * determinare e visualizzare il sottoinsieme di intervalli compatibili che massimizza la somma delle durate
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int estremo_inferiore;
    int estremo_superiore;
}interv;

void intervSel(int N,interv v[6]);
void powerset_combsempl(int pos,int start,int k,int *sol,interv *v,int N,int *bestsol,int *massimadurata,int *elementi);
int check(int *sol,int k,interv v[6]);

int main(){
    interv v[] = {{1,2},{2,4},{2,5},{3,5},{5,7},{6,8}};
    int N=6;
    intervSel(N,v);
    return 0;
}

void intervSel(int N,interv v[6]){
    //usare i powerset comb semplici
    int *sol = (int *) malloc(N*sizeof(int));
    int start=0;
    int pos=0;
    int *bestsol = (int *) malloc(N*sizeof(int));
    int massimadurata = 0;
    int elementi = 0;
    int i;

    for(i=1;i<=N;i++) powerset_combsempl(pos,start,i,sol,v,N,bestsol,&massimadurata,&elementi);

    printf("Somma durate: %d\n",massimadurata);
    for(i=0;i<elementi;i++) printf("(%d,%d) ",v[bestsol[i]].estremo_inferiore,v[bestsol[i]].estremo_superiore);

    free(bestsol);
    free(sol);

}

void powerset_combsempl(int pos,int start,int k,int *sol,interv *v,int N,int *bestsol,int *massimadurata,int *elementi){

    int i;
    int durata_tot;
    if(pos>=k){
        //for(i=0;i<k;i++) printf("(%d,%d) ",v[sol[i]].estremo_inferiore,v[sol[i]].estremo_superiore);
        //printf("\n");
        if(check(sol,k,v)){ //controllo se le attività sono compatibili
            durata_tot=0; //calcolo la durata, poi la confronto
            for(i=0;i<k;i++) durata_tot = durata_tot + (v[sol[i]].estremo_superiore - v[sol[i]].estremo_inferiore);
            if(durata_tot>(*massimadurata)){//se la stima migliora allora aggiorno variabili e best sol
                (*massimadurata)=durata_tot;
                (*elementi) = k;
                for(i=0;i<k;i++) bestsol[i] = sol[i];
            }
        }
        return;
    }

    for(i=start;i<N;i++){
        sol[pos] = i;
        powerset_combsempl(pos+1,i+1,k,sol,v,N,bestsol,massimadurata,elementi);
    }
}

int check(int *sol,int k,interv v[6]){
    int i,j;

    for(i=0;i<k;i++){ //confronto ogni attività del vettore sol[K] con ogni elemento del vettore tranne se stesso ovviamente
        for(j=0;j<k;j++){
            if(i!=j) if((v[sol[i]].estremo_inferiore < v[sol[j]].estremo_superiore) && (v[sol[j]].estremo_inferiore < v[sol[i]].estremo_superiore)) return 0;
        }
    }


    return 1;
}
