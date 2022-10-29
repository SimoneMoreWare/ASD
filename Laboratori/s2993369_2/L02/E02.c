/*
 * gioco si svolge su scacchiera rettangolare RxC caselle
 *
 * in ogni casella deve essere posizionata una tessera
 * su cui sono disegnati due segmenti di tubo
 *      uno in orizzontale
 *      uno in verticale
 *      ogni segmento è caratterizato da
 *          un colore
 *          un punteggio (valore intero positivo)
 *          per ottenere i punti associati è necessario
 *              allineare lungo un'intera riga i tubi in orizzontale dello stesso colore
 *              allinea lungo un'intera colonna i tubi in verticale dello stesso colore
 *
 * le tessere possono essere ruotata di 90 gradi
 * le tessere sono disponibili in copia singola
 * si assuma esistano abbastanza tessere per completare la scacchiera
 *
 * OBIETTIVO
 * ottenere il massimo punteggio possibile posizionando una tessera in ogni cella della scacchiera
 *
 * file di testo tiles.txt è riportato l'elenco delle tessere disponibili nel segeunte formato
 *      sulla prima riga è presente il numero T di tessere
 *      seguono T quadruple nella forma
 *          <coloreT1><ValoreT1><coloreT2><valoreT2>
 *          a descrivere la coppia di tubi presenti sulla tessera
 * a ogni tessera è associato un identificativo numerico nell'intervallo 0...T-1
 *
 * Su un secondo file di testo board.txt è riportata una configurazione iniziale per la scacchiera di gioco
 *      sulla prima riga è presente una coppia di interi R e C a rappresentare il numero di righe e colonne della superficie di gioco
 *      seguono R righe riportanti C elementi ciascuna a definire la configurazione di ogni cella
 *      ogni cella è descritta da una coppia ti/r dove ti è l indice di una tessara tra quelle presenti in tiles.txt e r rappresenta l'eventuale sua rotazione
 *      (es: 7/0 oppure 3/1 per rappresentare rispettivamente una tessera non ruotata e una ruotata). Una cella vuota è rappresentata dalla coppia -1/-1.
 */
#include <stdio.h>
#include <stdlib.h>

#define tilesname "../log.txt"
#define boardname "../brani.txt"

typedef struct{
    char col1,col2;
    int val1,val2;
    int mark;
}tessere_t;

typedef struct{
    tessere_t tessere;
    int rot;
    int used;
}cella_t;

tessere_t* leggitessere(int *ntessere);
cella_t** leggiboard(tessere_t *tessere,int *R,int *C);
int dispripetute(int pos, cella_t **board,tessere_t *tessere,int R,int C,int cnt);
void stampa(cella_t **board,int R,int C);
void swaprot(tessere_t *tessera);

int main(){
    int ntessere,R,C;
    tessere_t *tessere;
    cella_t **board;
    int pos=0;
    int cnt=0;
    tessere=leggitessere(&ntessere);
    board=leggiboard(tessere,&R,&C);
    cnt=dispripetute(pos,board,tessere,R,C,cnt);
    printf("%d",cnt);

    /*for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            if(board[i][j].used==1){
                printf("%c%d%c%d ",(board[i][j].tessere.col1),(board[i][j].tessere.val1),(board[i][j].tessere.col2),(board[i][j].tessere.val2));
            }else{
                printf("0 ");
            }
        }
        printf("\n");
    }*/
    //for(int i=0;i<ntessere;i++) printf("%c %d %c %d\n",(tessere[i].col1),(tessere[i].val1),(tessere[i].col2),(tessere[i].val2));
    return 0;
}

tessere_t* leggitessere(int *ntessere){
    int i;
    FILE *fp;
    tessere_t *ret;
    fp= fopen(tilesname,"r");
    if(fp!=NULL){
        fscanf(fp,"%d\n",&(*ntessere));
        ret=(tessere_t *) malloc((*ntessere)*sizeof(tessere_t));
        for(i=0;i<(*ntessere);i++) fscanf(fp,"%c %d %c %d\n",&(ret[i].col1),&(ret[i].val1),&(ret[i].col2),&(ret[i].val2));
    }else{
        printf("Problemi con il file tiles");
        exit(0);
    }
    fclose(fp);
    return ret;
}

cella_t** leggiboard(tessere_t *tessere, int *R,int *C){
    int i,j;
    int t,r;
    FILE *fp;
    cella_t **ret;
    fp=fopen(boardname,"r");
    if(fp!=NULL){
        fscanf(fp,"%d %d\n",&(*R),&(*C));

        ret=(cella_t **) malloc(((*R))*sizeof(cella_t *));
        for(i=0;i<(*C);i++) ret[i]=(cella_t *) malloc(((*C))*sizeof(cella_t));

        for(i=0;i<(*C);i++){
            for(j=0;j<(*R);j++) {
                fscanf(fp,"%d%*c%d",&t,&r);
                if(t==-1 && r==-1){
                    ret[i][j].rot=-1;
                    ret[i][j].used=0;
                    tessere[t].mark=0;
                }else if(r==0){
                    ret[i][j].tessere=tessere[t];
                    ret[i][j].rot=0;
                    ret[i][j].used=1;
                    tessere[t].mark=1;
                }else if(r==1){
                    swaprot(&(tessere[t]));
                    ret[i][j].tessere=tessere[t];
                    ret[i][j].rot=0;
                    ret[i][j].used=1;
                    tessere[t].mark=1;
                }
            }
        }
    }else{
        printf("Problemi con il file board");
        exit(1);
    }
    fclose(fp);
    return ret;
}

int dispripetute(int pos, cella_t **board,tessere_t *tessere,int R, int C, int cnt){
    int i,j,k;
    if(pos>=(R*C)){
        stampa(board,R,C);
        return cnt+1;
    }
    i=pos/R; j=pos%R;
    if(board[i][j].used!=0){
        cnt=dispripetute(pos+1,board,tessere,R,C,cnt);
        return cnt;
    }
    for(k=0;k<(R*C);k++){
        if(!(tessere[k].mark)){
            board[i][j].used=1;
            board[i][j].tessere=tessere[k];
            tessere[k].mark=1;

            cnt=dispripetute(pos+1,board,tessere,R,C,cnt);

            board[i][j].used=0;
            tessere[k].mark=0;

        }
    }
    return cnt;
}

void stampa(cella_t **board,int R,int C){
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            if(board[i][j].used==1){
                printf("%c%d%c%d ",(board[i][j].tessere.col1),(board[i][j].tessere.val1),(board[i][j].tessere.col2),(board[i][j].tessere.val2));
            }else{
                printf("0 ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void swaprot(tessere_t *tessera){
    int tmpval; char tmpcol;
    tmpval=(*tessera).val1;
    (*tessera).val1=(*tessera).val2;
    (*tessera).val2=tmpval;
    tmpcol=(*tessera).col1;
    (*tessera).col1=(*tessera).col2;
    (*tessera).col2=tmpcol;
}

