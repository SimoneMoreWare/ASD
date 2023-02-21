#include <stdio.h>

#define MAXR 19
#define MAXC 19

/* versione con uso di funzioni per input mossa, controllo della vittoria
e stampa della tabella */
/* la funzione controllaMossa cerca di unificare i diversi tipi di controllo,
trovanto una unica formulazione per percorso su riga, colonna, diagonale e
antidiagonale */
/* il conteggio della lunghezza di una sequenza lungo una direzione e' disaccoppiato
dalla funzione di verifica ed e' implementato dalla funzione contaPedineDirezione
*/

void leggiMossa(char tab[MAXR][MAXC+1], char colore, int mossa[2]);
int controllaMossa (char tab[MAXR][MAXC+1], int mossa[2]);
int contaPedineDirezione(char t[MAXR][MAXC+1], int mossa[2], int direzione[2]);
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
un parametro ulteriore vettore (mossa) di due caselle: poiche' il vettore e' (di fatto)
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

/* la funzione contaPedineDirezione conta il numero di pedine adiacenti, a partire
dalla posizione passata tramite il parametro mossa, lungo la direzione
passata tramite il parametro direzione. Come per la mossa, si e' scelto di utilizzare
un vettore di due elementi per rappresentare la direzione.
 */

int contaPedineDirezione(char t[MAXR][MAXC+1], int mossa[2], int direzione[2]) {

    int r, c, cnt, i, j, vittoria, dx, dy, col;
  
    r = mossa[0];
    c = mossa[1];
    col = t[r][c];
  
    vittoria = 0;

    /* spostamento lungo righe e colonne */
    dx = direzione[0];
    dy = direzione[1];

    /* caselle a "sinistra" */
    for (i =r-dx,j=c-dy,cnt=1;
         i>=0 && j>=0 && i<MAXR && j<MAXC && t[i][j]==col;
         i-=dx,j-=dy)
        cnt++;
    /* caselle a "destra" */
    for (i =r+dx,j=c+dy;
         i>=0 && j>=0 && i<MAXR && j<MAXC && t[i][j]==col;
         i+=dx,j+=dy)
        cnt++;
    
    return cnt;
    
}

int controllaMossa (char t[MAXR][MAXC+1], int mossa[2])
{
    int cnt, k, vittoria;
    int delta[4][2] = {
        {0,1}, /* riga: indice di riga non cambia, spostamento di 1 su colonna */
        {1,0}, /* colonna: spostamento di 1 su riga, indice di colonna non cambia  */
        {1,1}, /* diagonale: indici sia di riga che di colonna incrementati di 1 */
        {1,-1} /* anti-diagonale: indice di riga incrementato di 1, -1 per la colonna */
    };
    
    /* se nessun controllo ha successo restera' a 0 */
    vittoria = 0;
    
    /* k=0: riga, k=1: colonna, k=2: diagonale, k=3: anti-diagonale */
    for (k=0; k<4 && !vittoria; k++)
        /* si noti l'assegnazione al flag vittoria del risultato di una espressione logica */
        vittoria = (contaPedineDirezione(t, mossa, delta[k]) >= 5);
	/* Nota: una volta che vittoria diventa vero si esce dal ciclo */

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
