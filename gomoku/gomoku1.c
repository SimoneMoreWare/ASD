#include <stdio.h>

#define MAXR 19
#define MAXC 19

/* versione senza uso di funzioni e con gestione esplicita di tutti i casi */
/* si noti come molti casi simili sono ripetuti */

int main (int argc, char *argv[])
{
    char tab[MAXR][MAXC];
    FILE *fp;
    int i,j,r,c,cnt,finito=0, ok;
    
    fp = fopen(argv[1],"r");
    /* lettura della matrice carattere per carattere */
    for (i=0; i<MAXR; i++) {
        for (j=0; j<MAXC; j++)
            fscanf(fp,"%c",&tab[i][j]);
        fscanf(fp,"\n");
    }
    fclose(fp);
    
    while (!finito) {
        
        /* se nessun controllo ha successo sara' rimesso a 0 */
        finito = 1;
        /* stampa situazione */
        printf("tabella aggiornata\n");
        for (i=0; i<MAXR; i++) {
            for (j=0; j<MAXC; j++)
                printf("%c",tab[i][j]);
            printf("\n");
        }
        
        /* NERO */
        do {
            printf("Mossa del nero: ");
            scanf("%d%d",&r,&c);
            r--; c--; /* porta le coordinate dall'intervallo 1..19 a 0..18 */
            if (r<0 || r>=MAXR || c<0 || c>=MAXC || tab[r][c]!='.') {
                printf("mossa non valida. ripetere.\n");
                ok = 0;
            }
            else {
                tab[r][c] = 'N';
                ok = 1;
            }
        } while (!ok);
        
        /* controlla riga: conta caselle dello steso colore a destra
        e a sinistra */
        /* caselle a sinistra */
        for (j=c-1,cnt=1; j>=0 && tab[r][j]=='N'; j--)
            cnt++;
        /* caselle a destra */
        for (j=c+1; j<MAXC && tab[r][j]=='N'; j++)
            cnt++;
        if (cnt>=5) {
            printf("vittoria del nero\n");
        }
        else {
            /* non c'e' vittoria su riga */
            /* controlla colonna: caselle sopra e sotto */
            /* caselle sopra */
            for (i=r-1,cnt=1; i>=0 && tab[i][c]=='N'; i--)
                cnt++;
            /* caselle a sotto */
            for (i=r+1; i<MAXR && tab[i][c]=='N'; i++)
                cnt++;
            if (cnt>=5) {
                printf("vittoria del nero\n");
            }
            else {
                /* non c'e' vittoria su riga o colonna */
                /* controlla diagonale */
                /* caselle sopra/sinistra */
                for (i=r-1,j=c-1,cnt=1; i>=0 && j>=0 && tab[i][j]=='N'; i--,j--)
                    cnt++;
		/* In alternativa:
		int k;
                for (k=1, cnt=1; i-k >= 0 && j-k >= 0 && tab[i-k][j-k]=='N'; k++)
                    cnt++;
		*/
                /* caselle sotto/destra */
                for (i=r+1,j=c+1; i<MAXR && j<MAXC && tab[i][j]=='N'; i++,j++)
                    cnt++;
                if (cnt>=5) {
                    printf("vittoria del nero\n");
                }
                else {
                    /* non c'e' vittoria su riga, colonna o diagonale */
                    /* controlla anti-diagonale */
                    /* caselle sopra/destra */
                    for (i=r-1,j=c+1,cnt=1; i>=0 && j<MAXC && tab[i][j]=='N'; i--,j++)
                        cnt++;
                    /* caselle sotto/sinistra */
                    for (i=r+1,j=c-1; i<MAXR && j>=0 && tab[i][j]=='N'; i++,j--)
                        cnt++;
                    if (cnt>=5) {
                        printf("vittoria del nero\n");
                    }
                    else {
                        
                        /* BIANCO */
                        do {
                            printf("Mossa del bianco: ");
                            scanf("%d%d",&r,&c);
                            r--; c--; /* porta le coordinate dall'intervallo 1..19 a 0..18 */
                            if (r<0 || r>=MAXR || c<0 || c>=MAXC || tab[r][c]!='.') {
                                printf("mossa non valida. ripetere.\n");
                                ok = 0;
                            }
                            else {
                                tab[r][c] = 'B';
                                ok = 1;
                            }
                        } while (!ok);
                        
                        /* controlla riga */
                        /* caselle a sinistra */
                        for (j=c-1,cnt=1; j>=0 && tab[r][j]=='B'; j--)
                            cnt++;
                        /* caselle a destra */
                        for (j=c+1; j<MAXC && tab[r][j]=='B'; j++)
                            cnt++;
                        if (cnt>=5) {
                            printf("vittoria del bianco\n");
                        }
                        else {
                            /* controlla colonna */
                            /* caselle sopra */
                            for (i=r-1,cnt=1; i>=0 && tab[i][c]=='B'; i--)
                                cnt++;
                            /* caselle a destra */
                            for (i=r+1; i<MAXR && tab[i][c]=='B'; i++)
                                cnt++;
                            if (cnt>=5) {
                                printf("vittoria del bianco\n");
                            }
                            else {
                                /* controlla diagonale */
                                /* caselle sopra/sinistra */
                                for (i=r-1,j=c-1,cnt=1; i>=0 && j>=0 && tab[i][j]=='B'; i--,j--)
                                    cnt++;
                                /* caselle sotto/destra */
                                for (i=r+1,j=c+1; i<MAXR && j<MAXC && tab[i][j]=='B'; i++,j++)
                                    cnt++;
                                if (cnt>=5) {
                                    printf("vittoria del bianco\n");
                                }
                                else {
                                    /* controlla anti-diagonale */
                                    /* caselle sopra/destra */
                                    for (i=r-1,j=c+1,cnt=1; i>=0 && j<MAXC && tab[i][j]=='B'; i--,j++)
                                        cnt++;
                                    /* caselle sotto/sinistra */
                                    for (i=r+1,j=c-1; i<MAXR && j>=0 && tab[i][j]=='B'; i++,j--)
                                        cnt++;
                                    if (cnt>=5) {
                                        printf("vittoria del bianco\n");
                                    }
                                    else {
                                        finito=0;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            
        }
        
    }
    
}
