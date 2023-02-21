#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void decomponi(char *str,int num,int *lungh);
void decomponiR(int pos,int start,int num,int *sol,char *str,int *lungh);
int checksol(int *sol, char *str,int num);

int flag=0;
int main(){
    char str[]="tentativo";
    int num=2;
    int lungh[]={2,4};
    decomponi(str,num,lungh);
    return 0;
}

void decomponi(char *str,int num,int *lungh){
    int *sol=(int *) malloc(num*sizeof(int));
    int pos=0;
    int start=0;
    decomponiR(pos,start,num,sol,str,lungh);
    if(flag==0) printf("non vi sono decomposizioni");
    free(sol);
}
//combinazioni ripetute
void decomponiR(int pos,int start,int num,int *sol,char *str,int *lungh){
    int i,j,k,u;
    if(pos==num){ //ho riempito il vettore sol con i vari elementi di lungh, combinati tra loro

        if(checksol(sol,str,num)) { //controllo se la lunghezza delle varie sottostringhe raggiungono la lunghezza della stringa
            for(j=0;j<num;j++) printf("%d ",sol[j]);
            printf("\n");
            u = 0;
            for (j = 0; j < num; j++) {
                for (k = 0; k < sol[j]; k++) printf("%c", str[u++]);
                printf(" ");
            }
            flag=1; //faccio solo un caso
        }
        return;
    }
    //modello della combinazioni ripetute 
    for(i=start;i<num && flag==0;i++){ 
        sol[pos]=lungh[i];
        decomponiR(pos+1,start,num,sol,str,lungh);
        start++;
    }
}

int checksol(int *sol,char *str,int num){
    int i;
    int res=0;
    for(i=0;i<num;i++) res=res+sol[i];
    if(res==strlen(str)) return 1;
    return 0;
}

/*
La funzione main() del programma prende in input una stringa "tentativo" e un intero "num", che in questo caso è pari a 2. Inoltre, viene dichiarato un array di interi "lungh" di lunghezza "num", che in questo caso contiene i valori 2 e 4.
Viene poi chiamata la funzione "decomponi" passandole come argomenti la stringa "str", l'intero "num" e l'array "lungh".

La funzione "decomponi" alloca dinamicamente un array di interi "sol" di lunghezza "num" e inizializza due variabili interne "pos" e "start" a 0. Successivamente, chiama la funzione "decomponiR" passandole come argomenti "pos", "start", "num", "sol", "str" e "lungh".

La funzione "decomponiR" è una funzione ricorsiva che prende in input sei argomenti: "pos", "start", "num", "sol", "str" e "lungh".
La funzione controlla se "pos" è uguale a "num". Se è così, significa che è stata trovata una possibile decomposizione della stringa "str" in "num" sottostringhe di lunghezza specificata dall'array "lungh".
La funzione "decomponiR" chiama quindi la funzione "checksol" passandole come argomenti "sol", "str" e "num". Se "checksol" restituisce 1, significa che la decomposizione è valida e quindi viene stampata sullo schermo. In caso contrario, la funzione "decomponiR" termina l'esecuzione.

La funzione "checksol" prende in input tre argomenti: "sol", "str" e "num". Somma gli elementi dell'array "sol" e controlla se la somma è uguale alla lunghezza della stringa "str". Se è così, restituisce 1. Altrimenti, restituisce 0.

La funzione "decomponi" alloca dinamicamente un array di interi "sol" di lunghezza "num" e inizializza due variabili interne "pos" e "start" a 0. Successivamente, chiama la funzione "decomponiR" passandole come argomenti "pos", "start", "num", "sol", "str" e "lungh".
La funzione "decomponiR" è una funzione ricorsiva che prende in input sei argomenti: "pos", "start", "num", "sol", "str" e "lungh".
*/
