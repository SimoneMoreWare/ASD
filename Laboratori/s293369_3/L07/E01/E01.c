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
#define MAXELEMENTI 5
#define filename "../elementi.txt"

int cnt=0;
int MAXDIAG=1000000;

/*typedef enum{
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
}azione;*/

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

typedef struct{
    elemento elementi[MAXELEMENTI];
    int num_elementi_utilizzati;
}diagonale;

elemento* leggifile(int *dim);
void leggivalori(elemento **res,FILE *fp, int i);
void powerset(elemento *elementi,int dim, diagonale *diagonali);
void powerset_r(elemento* elementi, int dim, elemento* sol, int j, int pos,int start,int dd,int dp,diagonale** diagonali,int finale,int direzione);
int check(elemento* elementi, int i, int dd,int pos,elemento* sol,int direzione);
void combinazioniripetute(int pos,diagonale *diagonali,diagonale *sol_d,int k,int start,int dd,int dp,double *maxscore,diagonale **risultato);
int checkprogramma(int pos,diagonale *diagonali,int i,int dp,diagonale *sol_d);
int validate(diagonale *sol_d,int k);
double calcolascore(diagonale *sol_d,int k);
int main(){
    elemento *elementi;
    int dim;
    diagonale *diagonali=NULL;
    elementi=leggifile(&dim);
    powerset(elementi,dim,diagonali);
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

void powerset(elemento *elementi,int dim, diagonale *diagonali){
    int j;
    int maxelementi=5; //dato fornito dalla traccia
    elemento *sol_e;
    diagonale *sol_d;
    diagonale *risultato;
    double maxscore=0.0;
    int dd=7,dp=30;
    int pos=0;
    int k;
    int start=0;
    if(dim<maxelementi) maxelementi=dim;
    sol_e=(elemento *) malloc((maxelementi)*sizeof(elemento));
    diagonali=(diagonale *) malloc(MAXDIAG*sizeof(diagonale));
    for(j=1;j<=maxelementi;j++) powerset_r(elementi,dim,sol_e,j,pos,start,dd,dp,&diagonali,0,1);
    for(int i=0;i<cnt;i++){
        for(j=0;j<diagonali[i].num_elementi_utilizzati;j++){
            printf("%s ",diagonali[i].elementi[j].nome);
        }
        printf("\n");
    }
    pos=0;
    k=3;
    start=0;
    sol_d=(diagonale *) malloc(k*sizeof(diagonale));
    risultato=(diagonale *) malloc(k*sizeof(diagonale));
    combinazioniripetute(pos,diagonali,sol_d,k,start,dd,dp,&maxscore,&risultato);
    printf("%0.3lf\n",maxscore);
    /*for(int i=0;i<k;i++){
        for(int h=0;h<risultato[i].num_elementi_utilizzati;h++){
            printf("%s ",risultato[i].elementi[h].nome);
        }
        printf("\n---\n");
    }*/

}

//disp ripetute
void powerset_r(elemento* elementi, int dim, elemento* sol, int j, int pos,int start,int dd,int dp,diagonale** diagonali,int finale,int direzione){
    int i;
    int tmp=0;
    if(pos>=j || finale==1){
        //printf("{ ")
        for(i=0;i<j;i++){
            if(cnt<MAXDIAG){
                (*diagonali)[cnt].num_elementi_utilizzati=pos;
                (*diagonali)[cnt].elementi[i]=sol[i];
                tmp=tmp+sol[i].diffcolta;
               // (*diagonali)[cnt]=sol[i];
               //printf("Manda");
            }else{
                //ci sono piu condiserazione da fare
                (*diagonali)=realloc((*diagonali),(2*MAXDIAG)*sizeof(elemento ***));
                MAXDIAG=2*MAXDIAG;
            }
        }
        printf("%d\n",tmp);
        cnt++;
        return;
    }
    for(i=start;i<dim;i++) {
        if (check(elementi,i,dd,pos,sol,direzione)) {
            sol[pos] = elementi[i];
            powerset_r(elementi, dim, sol, j, pos + 1, i + 1, dd,dp,diagonali,elementi[i].finale,elementi[i].direzionediuscita);
            //start++;
        }
    }
}


int check(elemento* elementi, int i, int dd,int pos,elemento* sol,int direzione){
    int ddpartial=0;
    int j;
    if(pos!=0 && sol[0].direzionediingresso!=0) return 0; //direzionediingressofrontale
    if(pos!=0 && sol[0].requisitodiprecedenza!=0) return 0; //direzionediingressofrontale
    for(j=0;j<pos;j++) ddpartial=ddpartial+sol[j].diffcolta;
    if((elementi[i].diffcolta+ddpartial)<=dd) return 1; //somma elementi < dd
    return 0;
}

void combinazioniripetute(int pos,diagonale *diagonali,diagonale *sol_d,int k,int start,int dd,int dp,double *maxscore,diagonale **risultato){
    int i,j;
    int dpscore=0;
    double score;
    if(pos>=k){
        if(validate(sol_d,k)) {
            score=calcolascore(sol_d,k);
            if(score>(*maxscore)){
                (*maxscore)=score;
                for(j=0;j<k;j++) (*risultato)[j]=sol_d[j];
            }

           /* for (i = 0; i < k; i++) {
                for (j = 0; j < sol_d[i].num_elementi_utilizzati; j++) {
                    dpscore = dpscore + sol_d[i].elementi[j].diffcolta;
                    printf("%s ", sol_d[i].elementi[j].nome);
                }
                printf("| ");
            }
            printf("DPeff %d", dpscore);
            printf("\n-----\n");*/
        }
        return;
    }
    for(i=start;i<cnt;i++){
        if(checkprogramma(pos,diagonali,i,dp,sol_d)){
            sol_d[pos]=diagonali[i];
            combinazioniripetute(pos+1,diagonali,sol_d,k,start,dd,dp,maxscore,risultato);
            start++;
        }
    }
}

int checkprogramma(int pos,diagonale *diagonali,int i,int dp,diagonale *sol_d){
    int dppartial=0;
    int j,u;
    for(j=0;j<pos;j++) for(u=0;u<sol_d[j].num_elementi_utilizzati;u++) dppartial=dppartial+sol_d[j].elementi[u].diffcolta;
    for(u=0;u<diagonali[i].num_elementi_utilizzati;u++) dppartial=dppartial+diagonali[i].elementi[u].diffcolta;
    if(dppartial<=dp) return 1;
    return 0;
}

int validate(diagonale *sol_d,int k){
    int checkavanti=0,checkindietro=0;
    int checksequenza=0;
    int i,j;
    for (i = 0; i < k; i++) {
        for (j = 0; j < sol_d[i].num_elementi_utilizzati; j++) {
            if(sol_d[i].elementi[j].tipologia==1 && checkindietro!=1) checkindietro=1;
            if(sol_d[i].elementi[j].tipologia==2 && checkavanti!=1) checkavanti=1;
            if(j!=(sol_d[i].num_elementi_utilizzati-1) && sol_d[i].elementi[j].direzionediuscita==sol_d[i].elementi[j+1].direzionediingresso) checksequenza=1;
        }
    }
    if(checkavanti==1 && checkindietro==1 && checksequenza==1) return 1;
    return 0;
}

double calcolascore(diagonale *sol_d,int k){
    int i,j;
    double res=0;
    for (i = 0; i < k; i++) {
        for (j = 0; j < sol_d[i].num_elementi_utilizzati; j++) {
            res=res+sol_d[i].elementi[j].valore;
        }
    }
    return res;
}
