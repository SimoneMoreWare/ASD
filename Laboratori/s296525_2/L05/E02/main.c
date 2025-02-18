#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    FALSE,
    TRUE
} bool;

/*
 * struttura dati che permette di incapsulare i valori
 * per la riga (posizione 0) e per la colonna (posizione 1).
 * 
 * C = vettore di caratteri che identificano il colore
 *     assegnato alla riga (0) o alla colonna (1)
 * V = vettore dei valori assegnati alla riga (0)
 *     o alla colonna (1)
 * taken = booleano che definisce se la tessera è già
 *         stata presa
 */
typedef struct {
    char C[2];
    int V[2];
    bool taken;
} tile;

/*
 * struttura dati che permette di definire una cella
 * della scacchiera.
 * 
 * tile = codice (posizione nel vettore di elementi tile)
 *        della tessera inserita, -1 se è vuota
 * r = rotazione della tessera (0 se non ruotato, 1 se ruotato)
 */
typedef struct {
    int tile, r;
} boardTile;

/*
 * funzione ricorsiva che permette di ottenere il punteggio massimo
 * per la scacchiera secondo le regole definite. 
 * la ricorsione termina quando si raggiunge la fine del vettore
 * di tessere disponibili t, poiché la scacchiera risulterà piena
 * per come vengono assegnate le tessere dalla funzione.
 * 
 * pos = posizione attuale nel vettore t
 * t = vettore di tessere disponibili
 * T = numero di tessere disponibili
 * board = scacchiera attuale
 * R = numero righe della scacchiera
 * C = numero colonne della scacchiera
 * max_board = scacchiera con punteggio massimo attuale
 * max = punteggio massimo attuale
 */
void get_max_score(int pos, tile* t, int T, boardTile*** board, int R, int C, boardTile*** max_board, int *max) {
    int i, j, k, current_max, tmp;

    if(pos >= T) {
        current_max = 0;
        /*
         * calcola il punteggio delle righe
         * 
         * NB: (*board)[j][0].r
         * 
         *     la rotazione viene utilizzata come indice del
         *     vettore di colori, poiché C[0] indica il colore
         *     della riga, mentre C[1] indica il colore della
         *     colonna.
         *     Ciò significa che, se il pezzo è stato ruotato,
         *     si avrà che C[1] indica il colore della riga, mentre
         *     C[0] indica il colore della colonna.
         */
        for(j = 0; j < R; j++) {
            tmp = 0;
            for(k = 0; k < C; k++)
                if(t[(*board)[j][0].tile].C[(*board)[j][0].r] == t[(*board)[j][k].tile].C[(*board)[j][k].r])
                    tmp = tmp + t[(*board)[j][k].tile].V[(*board)[j][k].r];
                else 
                    break;
            
            if (k == C) {
                current_max = current_max + tmp;
            }
        }

        /*
         * calcola il punteggio delle colonne
         *
         * NB: 1-(*board)[j][0].r
         * 
         *     la rotazione viene utilizzata come indice del
         *     vettore di colori, poiché C[1] indica il colore
         *     della colonna, mentre C[0] indica il colore della
         *     riga.
         *     Ciò significa che, se il pezzo è stato ruotato,
         *     si avrà che C[0] indica il colore della colonna, 
         *     mentre C[1] indica il colore della colonna.
         */
        for(k = 0; k < C; k++) {
            tmp = 0;
            for(j = 0; j < R; j++) {
                if(t[(*board)[0][k].tile].C[1-(*board)[0][k].r] == t[(*board)[j][k].tile].C[1-(*board)[j][k].r])
                    tmp = tmp + t[(*board)[j][k].tile].V[1-(*board)[j][k].r];
                else 
                    break;
            }
            if (j == R)
                current_max = current_max + tmp;
        }

        /*
         * controlla se il punteggio attuale è maggiore del massimo attuale
         */
        if(current_max > *max) {
            *max = current_max;
            for(j = 0; j < R; j++)
                for(k = 0; k < C; k++)
                    memcpy(&((*max_board)[j][k]), &((*board)[j][k]), sizeof(boardTile));
        }
        return;
    }

    for(i = pos; i < T; i++) {
        if(!t[i].taken) {
            for(j = 0; j < R; j++) {
                for(k = 0; k < C; k++) {
                    if((*board)[j][k].tile == -1) {
                        (*board)[j][k].tile = i;
                        t[i].taken = TRUE;
                        
                        // controlla entrambi gli orientamenti
                        (*board)[j][k].r = 0;
                        get_max_score(i+1, t, T, board, R, C, max_board, max);
                        (*board)[j][k].r = 1;
                        get_max_score(i+1, t, T, board, R, C, max_board, max);
                        
                        (*board)[j][k].tile = -1;
                        (*board)[j][k].r = -1;
                        t[i].taken = FALSE;
                    }
                }
            }
        } else {
            get_max_score(i+1, t, T, board, R, C, max_board, max);
        }
    }
}

int main() {
    FILE* file;
    tile* t;
    boardTile** board;
    boardTile** max_board;
    int T, R, C, i, j, max = 0;

    if((file = fopen("tiles.txt", "r")) == NULL) {
        printf("Non è stato possibile aprire il file tiles.txt.");
        return 1;
    }
    fscanf(file, "%d\n", &T);
    t = (tile*) malloc(T*sizeof(tile));
    for(i = 0; i < T; i++) {
        fscanf(file, "%c %d %c %d \n", &(t[i]).C[0], &(t[i]).V[0], &(t[i]).C[1], &(t[i]).V[1]);
        t[i].taken = FALSE;
    }
    fclose(file);

    if((file = fopen("board.txt", "r")) == NULL) {
        printf("Non è stato possibile aprire il file board.txt.");
        return 1;
    }
    fscanf(file, "%d %d", &R, &C);
    board = (boardTile**) malloc(R*sizeof(tile*));
    max_board = (boardTile**) malloc(R*sizeof(tile*));
    for(i = 0; i < R; i++) {
        board[i] = (boardTile*) malloc(C*sizeof(tile));
        max_board[i] = (boardTile*) malloc(C*sizeof(tile));
        for(j = 0; j < C; j++) {
            fscanf(file, "%d/%d", &(board[i][j].tile), &(board[i][j].r));
            if(board[i][j].tile != -1) {
                t[board[i][j].tile].taken = TRUE;
            }
        }
    }
    fclose(file);

    get_max_score(0, t, T, &board, R, C, &max_board, &max);

    printf("Punteggio massimo: %d\n", max);

    for(i = 0; i < R; i++) {
        for(j = 0; j < C; j++) {
            printf("%d/%d ", max_board[i][j].tile, max_board[i][j].r);
        }
        printf("\n");
    }

    return 0;
}