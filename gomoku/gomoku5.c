#include <stdio.h>
#include <string.h>

#define MAXR 19
#define MAXC 19

/* versione con uso di funzioni per input mossa, controllo della vittoria
e stampa della tabella
*/
/* la funzione controllaMossa cerca di unificare i diversi tipi di controllo,
trovanto una unica formulazione per percorso su riga, colonna, diagonale e
antidiagonale
*/
/* il conteggio della lunghezza di una sequenza lungo una direzione e' disaccoppiato
dalla funzione di verifica ed e' implementato dalla funzione contaPedineDirezione
*/
/* su aggiungono al programma base alcune caratteristiche NON richieste:
- si accetta una tabella più piccola del previsto (le dimensioni cono calcolate
al momento dell'input (servono quindi parametri aggiuntivi per le dimensioni effettive
- si accetta un comando per sospendere la partita
- se e' presente come ulteriore argomento al main un nome di file, vi si stampa
la tabella finale (o intermedia in caso di sospensione)
*/
/* in questa versione una mossa, anziche' da un vettore di due caselle, viene immagazzinata
in una struct di due campi (le coordinate), piu' un terzo che ne indica l'eventuale
richiesta di sospensione.
Un approcio analogo e' utilizzato per rappresentare una direzione: viene utilizzata una struct
con due campi (spostamento orizzontale e verticale).
*/

typedef struct mossa_s {
    int r;
    int c;
    int sospendi;
} mossa_t;

typedef struct dir_s {
    int dx;
    int dy;
} dir_t;

mossa_t leggiMossa(char tab[MAXR][MAXC+1], char colore, int nr, int nc);
int controllaMossa (char tab[MAXR][MAXC+1], mossa_t mossa, int nr, int nc);
int contaPedineDirezione(char t[MAXR][MAXC+1], mossa_t mossa, dir_t direzione, int nr, int nc);
void stampaTabella(FILE *fp, char tab[MAXR][MAXC+1], int nr, int nc);

int main (int argc, char *argv[])
{
    char tab[MAXR][MAXC+1];
    mossa_t mossa;
    FILE *fp;
    int i,j,r,c,cnt,finito=0, ok, nr, nc;
        
    fp = fopen(argv[1],"r");
    
    /* lettura della matrice per stringhe con rilevamento della lunghezza delle righe */
    /* si suppone matrice corretta con tutte le righe della stessa lunghezza */
    for (i=0; i<MAXR; i++) {
        /* una matrice di caratteri puo' essere usata come vettore di righe!!! */
        if (fscanf(fp,"%s",tab[i])==EOF) {
            break;
        }
        nc = strlen(tab[i]);
    }
    nr = i;
    fclose(fp);
    
    while (!finito) {
        
        stampaTabella(stdout,tab,nr,nc);
        /* NERO */
        mossa = leggiMossa(tab,'N',nr,nc);
        if (mossa.sospendi)
            break;
        finito = controllaMossa(tab,mossa,nr,nc);
        if (finito) {
            printf("vittoria del nero\n");
        }
        else {
            /* BIANCO */
            mossa = leggiMossa(tab,'B',nr,nc);
            if (mossa.sospendi)
                break;
            finito = controllaMossa(tab,mossa,nr,nc);
            if (finito) {
                printf("vittoria del bianco\n");
            }
        }
    }
    
    if (argc > 2) {
        printf("partita salvata su: %s\n", argv[2]);
        fp = fopen(argv[2],"w");
        stampaTabella(fp,tab,nr,nc);
        fclose(fp);
    }
    
}

/* Siccome la funzione deve ritornare tre valori (indici di riga e di colonna, e eventuale sospensione della partita), si utilizza una struct per impacchettare i valori. In alternativa, avremmo potuto:

   - usare un vettore di 3 elementi, sfruttando il fatto che la sospensione e' un valore booleano (vero/falso) rappresentabile con un int
   - passare un parametro addizionale tramite indirizzo:
       void leggiMossa(char t[MAXR][MAXC+1], char colore, int mossa[2], int *sospendi, int nr, int nc)
   - utilizzare la funzione della versione precedente, codificando la sospensione come mossa "-1 -1"
   - modificare la funzione della versione precedente facendo ritornare un valore booleano vero/falso a indicare la richiesta di sospensione della partita */

mossa_t leggiMossa(char t[MAXR][MAXC+1], char colore, int nr, int nc)
{
    int r, c, ok;
    mossa_t m = {0,0,0};
    do {
        if (colore=='B') printf("Mossa del bianco: ");
        else printf("Mossa del nero: ");
        scanf("%d%d",&r,&c);
        if (r==0 && c==0) {
            m.sospendi = 1;
            return m;
        }
        r--; c--; /* porta le coordinate dall'intervallo 1..19 a 0..18 */
        if (r<0 || r>=nr || c<0 || c>=nc || t[r][c]!='.') {
            printf("mossa non valida. ripetere.\n");
            ok = 0;
        }
        else {
            t[r][c] = colore;
            ok = 1;
        }
    } while (!ok);
    m.r = r;
    m.c = c;
    return m;
}


/* la funzione contaPedineDirezione conta il numero di pedine adiacenti, a partire
dalla posizione passata tramite il parametro mossa, lungo la direzione
passata tramite il parametro direzione. La direzione e' passata tramite il parametro
direzione, di tipo dir_t, ovvero una struct con due campi dx e dy.
 */

int contaPedineDirezione(char t[MAXR][MAXC+1], mossa_t mossa, dir_t direzione, int nr, int nc) {
  
    int r, c, cnt, i, j, vittoria, dx, dy, col;
    
    r = mossa.r;
    c = mossa.c;
    col = t[r][c];

    vittoria = 0;
    
    dx = direzione.dx;
    dy = direzione.dy;

    for (i =r-dx,j=c-dy,cnt=1;
         i>=0 && j>=0 && i<nr && j<nc && t[i][j]==col;
         i-=dx,j-=dy)
        cnt++;
    /* caselle a "destra" */
    for (i =r+dx,j=c+dy;
         i>=0 && j>=0 && i<nr && j<nc && t[i][j]==col;
         i+=dx,j+=dy)
        cnt++;
    
    return cnt;
    
    
}


int controllaMossa (char t[MAXR][MAXC+1], mossa_t mossa, int nr, int nc)
{
    int r, c, cnt, i, j, k, vittoria, dx, dy;

    dir_t delta[4] = {
      {0,1},
      {1,0},
      {1,1},
      {1,-1},
    };
    
    /* se nessun controllo ha successo restera' a 0 */
    vittoria = 0;
    
    /* k=0: riga, k=1: colonna, k=2: diagonale, k=3: anti-diagonale */
    for (k=0; k<4 && !vittoria; k++)
        /* si noti l'assegnazione al flag vittoria del risultato di una espressione logica */
        vittoria = (contaPedineDirezione(t, mossa, delta[k], nr, nc) >= 5);
        /* Nota: una volta che vittoria diventa vero si esce dal ciclo */
    
    return vittoria;
}

/* stampa tabella */
void stampaTabella(FILE *fp, char tab[MAXR][MAXC+1], int nr, int nc)
{
    int i, j;
    
    for (i=0; i<nr; i++) {
        for (j=0; j<nc; j++)
            fprintf(fp,"%c",tab[i][j]);
        fprintf(fp,"\n");
    }
}
