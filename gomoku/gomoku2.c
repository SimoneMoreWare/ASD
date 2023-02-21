#include <stdio.h>

#define MAXR 19
#define MAXC 19

/* versione con uso di funzioni per input mossa, controllo della vittoria
e stampa della tabella */
/* si noti come il programma risulti molto piu' compatto in quanto
le funzioni sono scritte una volta sola e chiamate per le mosse del
bianco e del nero */

/* una colonna in piu' per consentire input per righe (con una casella per '\0') */

void leggiMossa(char tab[MAXR][MAXC+1], char colore, int mossa[2]);
int controllaMossa (char tab[MAXR][MAXC+1], int mossa[2]);
void stampaTabella(FILE *fp, char tab[MAXR][MAXC+1]);

int main (int argc, char *argv[])
{
    char tab[MAXR][MAXC+1];
    int mossa[2];
    FILE *fp;
    int i,j,r,c,cnt,finito=0, ok;
    
    fp = fopen(argv[1],"r");
    /* lettura della matrice per stringhe */
    for (i=0; i<MAXR; i++) {
        /* una matrice di caratteri puo' essere usata come vettore di righe!!! */
        fscanf(fp,"%s",tab[i]);
    }
    fclose(fp);
    
    while (!finito) {
        
        stampaTabella(stdout,tab);
        /* NERO */
        leggiMossa(tab, 'N', mossa);
        finito = controllaMossa(tab,mossa);
        if (finito) {
            printf("vittoria del nero\n");
        }
        else {
            /* BIANCO */
            leggiMossa(tab, 'B', mossa);
            finito = controllaMossa(tab,mossa);
            if (finito) {
                printf("vittoria del bianco\n");
            }
        }
        
    }
    
}

/* siccome la funzione deve ritornare due valori (indici di riga e di colonna), si utilizza
un parametro ulteriore vettore (mossa) di due caselle: siccome il vettore e' (di fatto)
passato per riferimento (by reference) i valori assegnati sono visibili al programma
chiamante */
void leggiMossa(char t[MAXR][MAXC+1], char colore, int mossa[2])
{
    int r, c, ok;
    do {
        if (colore=='B') printf("Mossa del bianco: ");
        else printf("Mossa del nero: ");
        scanf("%d%d",&r,&c);
        r--; c--; /* porta le coordinate dall'intervallo 1..19 a 0..18 */
        if (r<0 || r>=MAXR || c<0 || c>=MAXC || t[r][c]!='.') {
            printf("mossa non valida. ripetere.\n");
            ok = 0;
        }
        else {
            t[r][c] = colore;
            ok = 1;
        }
    } while (!ok);
    mossa[0] = r;
    mossa[1] = c;
}

int controllaMossa (char t[MAXR][MAXC+1], int mossa[2])
{
    int i, j, r, c, cnt, vittoria;
    char col;
    
    r = mossa[0];
    c = mossa[1];
    col = t[r][c];
    
    /* se nessun controllo ha successo sara' rimesso a 0 */
    vittoria = 1;
    
    /* controlla riga */
    /* caselle a sinistra */
    for (j=c-1,cnt=1; j>=0 && t[r][j]==col; j--)
        cnt++;
    /* caselle a destra */
    for (j=c+1; j<MAXC && t[r][j]==col; j++)
        cnt++;
    if (cnt<5) {
        /* controlla colonna */
        /* caselle sopra */
        for (i=r-1,cnt=1; i>=0 && t[i][c]==col; i--)
            cnt++;
        /* caselle sotto */
        for (i=r+1; i<MAXR && t[i][c]==col; i++)
            cnt++;
        if (cnt<5) {
            /* controlla diagonale */
            /* caselle sopra/sinistra */
            for (i=r-1,j=c-1,cnt=1; i>=0 && j>=0 && t[i][j]==col; i--,j--)
                cnt++;
            /* caselle sotto/destra */
            for (i=r+1,j=c+1; i<MAXR && j<MAXC && t[i][j]==col; i++,j++)
                cnt++;
            if (cnt<5) {
                /* controlla anti-diagonale */
                /* caselle sopra/destra */
                for (i=r-1,j=c+1,cnt=1; i>=0 && j<MAXC && t[i][j]==col; i--,j++)
                    cnt++;
                /* caselle sotto/sinistra */
                for (i=r+1,j=c-1; i<MAXR && j>=0 && t[i][j]==col; i++,j--)
                    cnt++;
                if (cnt<5) {
                    /* nessun controllo ha avuto successo: vottoria=0 */
                    vittoria = 0;
                }
            }
        }
    }
    return vittoria;
}

/* stampa tabella */
void stampaTabella(FILE *fp, char tab[MAXR][MAXC+1]) {
    int i, j;
    
    for (i=0; i<MAXR; i++) {
        for (j=0; j<MAXC; j++)
            fprintf(fp,"%c",tab[i][j]);
        fprintf(fp,"\n");
    }
}
