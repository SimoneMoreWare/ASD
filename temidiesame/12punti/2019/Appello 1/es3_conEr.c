/*
	un nastro lungo n intero
	può essere tagliato in m (intero) diverse lunghezze intere lun
		1<=lun<=n
	ciascuno dei pezzi viene venduto ad un determinato prezzo
	si possono tagliare più pezzi della stessa lunghezza
	un vettore prezzo di m interi
		contiene i prezzi per ciascuna lunghezza
	un vettore lunghezza di m interi
		contiene le lunghezze ammesse

	si scriva una funzione C che noti
		n
		m
		lunghezze
		prezzo

		determinare come tagliare il nastro in modo da massimare il valore dei pezzi venduti
*/

#include <stdlib.h>
#include <stdio.h>


void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sort(int *lunghezza, int *prezzo, int dim) {
    int i, j;
    for (i = 0; i < dim - 1; i++) {
        for (j = 0; j < dim - i - 1; j++) {
            if (lunghezza[j] > lunghezza[j + 1]) {
                swap(&lunghezza[j], &lunghezza[j + 1]);
                swap(&prezzo[j], &prezzo[j + 1]);
            }
        }
    }
}

void algoritmodiEr(int n,int mblocchiusati,int pos,int *sol,int *lunghezze,int *prezzo,int m,int *massimocosto,int *best,int *blocchires){

    int i,j;
    int lunghezza_singolo;
    int prezzo_totale;
    if(pos>=n){
        prezzo_totale=0;
        for(i=0;i<mblocchiusati;i++){
            //printf("{");
            lunghezza_singolo=0;
            for(j=0;j<n;j++){
                if(sol[j]==i){
                    //ho i miei blocchi
                    //printf("-");
                    lunghezza_singolo++;
                }
            }
            prezzo_totale=prezzo_totale+prezzo[lunghezza_singolo-1];
            //printf("%d ",lunghezza_singolo);

            if(prezzo_totale>(*massimocosto)){
                (*massimocosto)=prezzo_totale;
                (*blocchires)=mblocchiusati;
                for(i=0;i<n;i++) best[i]=sol[i];
            }
            //printf("}");

        }
        //printf("\n");
        return;
    }

    for(i=0;i<mblocchiusati;i++){
        sol[pos]=i;
        algoritmodiEr(n,mblocchiusati,pos+1,sol,lunghezze,prezzo,m,massimocosto,best,blocchires);
    }
    sol[pos]=mblocchiusati;
    algoritmodiEr(n,mblocchiusati+1,pos+1,sol,lunghezze,prezzo,m,massimocosto,best,blocchires);
}

void wrapper(int n,int m,int *lunghezze,int *prezzo){

    //ho ordinato lunghezze e creato corrispondenza indice-lunghezza-prezzo
    sort(lunghezze, prezzo, m);

    int *sol = (int *) malloc(n*sizeof(int));
    int pos = 0;
    int mblocchiusati=0;
    int massimocosto=0;
    int i,j;
    int blocchires=0;
    int *best= (int *) malloc(n*sizeof(int));
    algoritmodiEr(n,mblocchiusati,pos,sol,lunghezze,prezzo,m,&massimocosto,best,&blocchires);
    for(i=0;i<blocchires;i++){
            printf("{");
            for(j=0;j<n;j++){
                if(best[j]==i) {
                    printf("-");
                }
            }
            printf("}");
    }
    printf(" Prezzo: %d",massimocosto);
}



int main(){
    int m=4;
    int n=4;
    int lunghezza[8]={4,1,2,3};
    int prezzo[8]={9,1,5,8};
    wrapper(n,m,lunghezza,prezzo);
    return 0;
}
