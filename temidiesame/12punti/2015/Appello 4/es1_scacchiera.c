#include <stdio.h>
void piazzaalfiere(int scacchiera[][4],int n);
int main(){
    int scacchiera[][4]={{3,0,2,0},{0,1,0,0},{0,0,0,3},{2,0,1,0}};
    int n=4;
    piazzaalfiere(scacchiera,n);
    return 0;
}

void piazzaalfiere(int scacchiera[][4],int n){

    int i,j,k;
    int riga,colonna;
    int res=0;
    int rmbriga,rmbcolonna;
    int sommapartial;
    for(i=0;i<n*n;i++){
        riga=i/n;
        colonna=i%n;
        if(scacchiera[riga][colonna]==0){
            k=riga;
            sommapartial=0;
            for(j=colonna-1;j>=0 && k>0;j--) sommapartial=sommapartial+scacchiera[--k][j];
            k=riga;
            for(j=colonna+1;j<=(n-1) && k<(n-1);j++) sommapartial=sommapartial+scacchiera[++k][j];
            k=riga;
            for(j=colonna+1;j<=(n-1) && k>0;j++) sommapartial=sommapartial+scacchiera[--k][j];
            k=riga;
            for(j=colonna-1;j>=0 && k<(n-1); j--) sommapartial=sommapartial+scacchiera[++k][j];

            if(sommapartial>res){
                res=sommapartial;
                rmbriga=riga;
                rmbcolonna=colonna;
            }
        }
    }
    printf("%d %d %d",rmbriga+1,rmbcolonna+1,res);
}

/*
Questa funzione riceve come argomenti un array bidimensionale di interi, chiamato "scacchiera", e un intero "n".

Il suo scopo è quello di trovare la posizione di un alfiere nella scacchiera (rappresentata come un array di interi) in cui il numero di caselle che l'alfiere può raggiungere è massimo, e stampare sullo schermo le coordinate di questa posizione e il numero di caselle raggiungibili.

La funzione inizia con la dichiarazione di alcune variabili: "i", "j" e "k" sono contatori per i cicli "for"; "riga" e "colonna" sono le coordinate della cella correntemente esaminata nella scacchiera; "res" è il risultato attualmente più alto trovato per il numero di caselle raggiungibili; "rmbriga" e "rmbcolonna" sono le coordinate della cella con il massimo numero di caselle raggiungibili trovato finora.

La funzione quindi esegue un ciclo "for" su tutte le celle della scacchiera. Per ogni cella, se questa è vuota (cioè il suo valore è 0), viene calcolato il numero di caselle raggiungibili dall'alfiere posizionato su di essa, utilizzando quattro cicli "for" annessi.

Il numero totale di caselle raggiungibili viene salvato nella variabile "sommapartial". Se questo valore è maggiore di "res", il valore di "res" viene aggiornato e vengono memorizzate le coordinate della cella corrente in "rmbriga" e "rmbcolonna".

Alla fine del ciclo "for" principale, la funzione stampa le coordinate della cella con il massimo numero di caselle raggiungibili trovato, utilizzando il formato "riga colonna numero_caselle_raggiungibili".

Per stampare le coordinate delle celle, viene sommato 1 a "rmbriga" e "rmbcolonna", poiché le coordinate delle celle nella scacchiera vanno da 0 a n-1, mentre nella stampa devono andare da 1 a n.
*/
