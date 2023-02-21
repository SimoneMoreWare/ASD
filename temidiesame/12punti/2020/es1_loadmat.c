/*
 * Vettore V di N interi
 * elementi rappresentano in formato compresso una sequenza di numeri che deve essere inserita
 * in una matrice d M di interi e di r righe e c colonne
 * inserire per righe
 *
 * per decodificare la sequeza edvono essere considerati a coppia gli interi del vettore
 *      il primo elemento rappresenta il numero di volte
 *              con cui il secondo deve essere inserito nelle celle adiacenti sulla stessa riga di M
 * scrivere funzione
 *      riempire la matrice
 *          stampare il contenuto
 */

#include <stdio.h>

void buildAndPrint(int V[14], int N, int M[3][5], int r, int c);

int main(){
    int r=3;
    int c=5;
    int N=14;
    int V[]={2,1,2,17,1,3,4,8,1,6,3,7,2,5};
    int M[3][5];
    buildAndPrint(V,N,M,r,c);
    return 0;
}

void buildAndPrint(int V[14], int N, int M[3][5], int r, int c){

    int k;
    int ripetizioni;
    int valoredainserire;
    int t=0;
    int i,j;
    int riga,colonna;
    for(k=0;k<N;k=k+2){
        ripetizioni=V[k];
        valoredainserire=V[k+1];
        for(i=0;i<ripetizioni;i++){
            riga=t/c;
            colonna=t%c;
            t++;
            M[riga][colonna]=valoredainserire;
        }
    }

    for(i=0;i<r;i++){
        for(j=0;j<c;j++) printf("%d ",M[i][j]);
        printf("\n");
    }
}
