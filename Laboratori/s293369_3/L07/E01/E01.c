/*
 * corpo libero atleta deve:
 *      eseguire una sequenza di elementi
 *          eseguire una serie di passaggi acrobatici (diagonali)
 *              ogni diagonale è composta da uno o più elementi
 *              ogni elemento descritto da una serie di parametri
 *                  salvati in elementi.txt
 *                      numeri elementi riportato sulla prima riga del file
 *                  nome dell'elemento
 *                      stringa, max 100 char
 *                  tipologia
 *                      avanti 2
 *                      indietro 1
 *                      transizione 0
 *                  direzione di ingresso
 *                      entrare frontalmente 1
 *                      entrare di spalle 0
 *                  direzione di uscita
 *                      uscire frontalmente 1
 *                      uscire di spalle 0
 *                  requisito di preccdenza
 *                      elemento eseguito come primo di una sequenza 0
 *                      essere preceduto da un altro elemento 1
 *                  finale
 *                      elemento non può essere eseguito da altri elementi 1
 *                      o meno 0
 *                  valore
 *                      float
 *                      punteggio ottenuto dall'atleta per corettezza esecuzione di un elemento
 *                  difficolta
 *                      int
 *                      difficoltà esecuzione elemento
 *
 *                 due elementi possono essere eseguiti in sequenza se
 *                      la direzione di uscita del primo elemento == direzione di ingresso del secondo elemento
 *
 *                 un atleta inizia una diagonale sempre frontalmente
 *                      direzionediingresso[0]=1
 *
 *                 difficolta diagonale
 *                  somma difficoltà degli elementi che la compongono
 *
 *                difficolta gara
 *                  somma difficolta diagonali
 *
 *
 *                regole
 *                  3 diagonali
 *                  almeno un elemento acrobatico in ogni diagonale
 *                  nel programma ginnasta deve includere almeno un elemento acrobatico avanti e un elemento acrobatico indietro
 *                  il ginnasta deve presentare almeno una diagonale in cui compaiono almeno due elementi acrobatici in sequenza
 *                  se il ginnasta include un elemento finale di difficoltà 8 o superiore punteggio nell'ultima diagonale, il punteggio viene moltiplicato per 1.5
 *                  ogni diagonale al max 5 elementi
 *                  difficoltà diagonale <= DD
 *                  difficoltà programma <= DP
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXN 100
#define filename "../elementi.txt"

typedef enum{
    transizione,indietro,avanti
}movimento;

typedef enum{
    spalle,frontale
}posizione;

typedef enum{
    primo,preceduto
}requisito;

typedef enum{
    seguito,nonseguito
}azione;

typedef struct{
    char nome[MAXN];
    int tipologia;
    int direzionediingresso;
    int direzionediuscita;
    int requisitodiprecedenza;
    int finale;
    float valore;
    int diffcolta;
}elemento;

elemento* leggifile(int *dim);
void leggivalori(elemento **res,FILE *fp, int i);
int powerset(elemento *elementi,int dim);
int powerset_r(elemento* elementi, int dim, elemento* sol, int j, int pos,int start);

int main(){
    elemento *elementi;
    int dim;
    int cnt;
    elementi=leggifile(&dim);
    cnt=powerset(elementi,dim);
    printf("\n%d",cnt);
    return 0;
}

elemento* leggifile(int *dim){
    FILE *fp;
    elemento *res;
    int i;
    fp= fopen(filename,"r");
    if(fp!=NULL){
        fscanf(fp,"%d\n",&(*dim));
        res=(elemento *) malloc((*dim)*sizeof(elemento));
        for(i=0;i<(*dim);i++) leggivalori(&res,fp,i);
        return res;
    }else{
        printf("Errore file");
        return NULL;
    }
}

void leggivalori(elemento **res,FILE *fp,int i){
    fscanf(fp,"%s %d %d %d %d %d %f %d",
           ((*res)[i]).nome,
           &((*res)[i]).tipologia,
           &((*res)[i]).direzionediingresso,
           &((*res)[i]).direzionediuscita,
           &((*res)[i]).requisitodiprecedenza,
           &((*res)[i]).finale,
           &((*res)[i]).valore,
           &((*res)[i]).diffcolta
           );
}

int powerset(elemento *elementi,int dim){
    int cnt=0,j;
    int maxelementi=5; //dato fornito dalla traccia
    elemento *sol;
    int pos=0;
    int start=0;
    if(dim<maxelementi) maxelementi=dim;
    sol=(elemento *) malloc((dim)*sizeof(elemento));
    for(j=1;j<=maxelementi;j++) cnt=cnt+powerset_r(elementi,dim,sol,j,pos,start);
    return cnt;
}

int powerset_r(elemento* elementi, int dim, elemento* sol, int j, int pos,int start){
    int cnt=0,i;
    if(pos>=j){
        printf("{ ");
        for(i=0;i<j;i++) printf("%s ",sol[i].nome);
        printf(" }\n");
        return 1;
    }
    for(i=start;i<dim;i++){
        sol[pos]=elementi[i];
        cnt=cnt+ powerset_r(elementi,dim,sol,j,pos+1,i+1);
    }
    return cnt;
}
