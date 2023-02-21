#include <stdlib.h>
#include <stdio.h>

#define n_numeri 9
#define n_alfabeto 26

void initmark(int *mark_alfabeto,int *mark_numeri,int k);
void generatepasword(FILE *fout,int pos, char *alfabeto,char *numeri, int maxlen, char *password,int *mark_alfabeto,int *mark_numeri);

int main(){
    char alfabeto[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    char numeri[]={'0','1','2','3','4','5','6','7','8','9'};
    int pos=0;
    int maxlen=5;
    int k=2;
    char *password=(char *) malloc(maxlen*sizeof(char));
    int *mark_alfabeto=(int *) malloc(n_alfabeto*sizeof(int));
    int *mark_numeri=(int *) malloc(n_numeri*sizeof(int));
    FILE *fout= fopen("ot.txt","w");
    initmark(mark_alfabeto,mark_numeri,k);
    generatepasword(fout,pos,alfabeto,numeri,maxlen,password,mark_alfabeto,mark_numeri);
    fclose(fout);
    free(password);
    free(mark_numeri);
    free(mark_alfabeto);
    return 0;
}

void initmark(int *mark_alfabeto,int *mark_numeri,int k){
    int i;
    for(i=0;i<n_alfabeto;i++) mark_alfabeto[i]=k;
    for(i=0;i<n_numeri;i++) mark_numeri[i]=k;
}

void generatepasword(FILE *fout,int pos, char *alfabeto,char *numeri, int maxlen, char *password,int *mark_alfabeto,int *mark_numeri){
    int i;
    if(pos>=maxlen){
        fprintf(fout,"%s\n",password);
        return;
    }
    if(pos>=0 && pos<=2){
        for(i=0;i<n_alfabeto;i++){
            if(mark_alfabeto[i]>0){
                mark_alfabeto[i]--;
                password[pos]=alfabeto[i];
                generatepasword(fout,pos+1,alfabeto,numeri,maxlen,password,mark_alfabeto,mark_numeri);
                mark_alfabeto[i]++;
            }
        }
    }else if(pos>=3 && pos<=4){
        for(i=0;i<n_numeri;i++){
            if(mark_numeri[i]>0){
                mark_numeri[i]--;
                password[pos]=numeri[i];
                generatepasword(fout,pos+1,alfabeto,numeri,maxlen,password,mark_alfabeto,mark_numeri);
                mark_numeri[i]++;
            }
        }
    }
}

/*
Il codice proposto genera tutte le possibili password di 5 caratteri che soddisfano i requisiti specificati.

La funzione initmark inizializza gli array di marcatori mark_alfabeto e mark_numeri con il valore di k, 
che indica il numero massimo di volte che una lettera o una cifra possono comparire nella password.

La funzione generatepasword utilizza la ricorsione per generare tutte le password possibili. 
La funzione prende come parametri il file di output, la posizione corrente nella password,
gli array di lettere e cifre disponibili, la lunghezza massima della password, l'array che rappresenta la password corrente, e gli array di marcatori.

Se la posizione corrente è compresa tra 0 e 2 (ovvero se stiamo generando la prima, la seconda 
o la terza lettera della password), la funzione prova tutte le lettere dell'alfabeto. 
Se invece la posizione corrente è compresa tra 3 e 4 (ovvero se stiamo generando l'ultima 
o l'ultima ma una cifra della password), la funzione prova tutte le cifre. In entrambi i casi,
per ogni lettera o cifra scelta, la funzione decrementa il relativo marcatore e chiama se stessa 
per generare le password successive. Al ritorno dalla chiamata ricorsiva, il marcatore viene incrementato di nuovo.

Quando la posizione corrente raggiunge la lunghezza massima della password (5), la funzione stampa 
la password corrente nel file di output e termina la ricorsione.


*/
