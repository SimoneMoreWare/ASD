#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int s, f, d;
} att;

/* 
 * Funzione ricorsiva che utilizza il modello delle disposizioni 
 * semplici per ottenere il vettore con durata massima
 * 
 * pos = posizione attuale in v
 * N = dimensione del vettore v
 * v = vettore di att
 * cnt = dimensione attuale della soluzione che si sta controllando
 * sol = soluzione che si sta controllando
 * d_max = durata della soluzione massima attuale
 * N_max = dimensione della soluzione massima attuale
 * sol_max = soluzione massima attuale
 */
void attSel_r(int pos, int N, att *v, att* sol, int cnt, int *d_max, int* N_max, att* sol_max) {
    int i, tmp = 0;
    
    if(pos >= N) {
        for(i = 0; i < cnt; i++) {
            tmp = tmp + sol[i].d;
        }

        if(*d_max < tmp) {
            *d_max = tmp;
            memcpy(sol_max, sol, cnt*sizeof(att));
            *N_max = cnt;
        }
        return;
    }

    for(i = pos; i < N; i++) 
        if(sol[cnt-1].s < v[i].f && sol[cnt-1].f <= v[i].s) { // se è valida
            sol[cnt] = v[i];
            attSel_r(pos+1, N, v, sol, cnt+1, d_max, N_max, sol_max);
        } else
            attSel_r(pos+1, N, v, sol, cnt, d_max, N_max, sol_max);
}

/*
 * Wrapper per la funzione ricorsiva, che inizializza
 * il vettore della soluzione finale e il vettore soluzione
 * per ogni passo, e infine stampa la soluzione trovata con
 * durata massima
 * 
 * N = dimensione del vettore di att
 * v = vettore di att
 */
void attSel(int N, att *v) {
    int i, d_max = 0, n_max = 0;
    att *sol, *sol_max;
    sol = (att*) malloc(N*sizeof(att));
    sol_max = (att*) malloc(N*sizeof(att));

    for(i = 0; i < N; i++) {
        sol[0] = v[i];
        attSel_r(i+1, N, v, sol, 1, &d_max, &n_max, sol_max);
    }

    printf("La soluzione ha durata massima %d.\n", d_max);
    for(i = 0; i < n_max; i++) {
        printf("(%d, %d) ", sol_max[i].s, sol_max[i].f);
    }
    printf("\n");
    free(sol);
}

int main() {
    int N, i;
    att *v;
    FILE* file;

    if((file = fopen("att.txt", "r")) == NULL) {
        printf("Il file è vuoto.\n");
        return 1;
    }

    fscanf(file, "%d", &N);
    v = (att*) malloc(N*sizeof(att));

    for(i = 0; i < N; i++) {
        fscanf(file, "%d", &(v[i].s));
        fscanf(file, "%d", &(v[i].f));
        v[i].d = v[i].f - v[i].s;
    }

    attSel(N, v);

    return 0;
}