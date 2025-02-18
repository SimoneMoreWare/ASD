#include "DISTMATR.h"

typedef struct distmatr_t {
    int **m;
    int N;
} *DISTMATR;

DISTMATR DISTMATRinit(int N) {
    int i;
    DISTMATR d = (DISTMATR) malloc(sizeof(*d));

    d->N = N;
    d->m = (int**) malloc(d->N*sizeof(int*));
    for (i = 0; i < d->N; i++)
        d->m[i] = (int*) malloc(d->N*sizeof(int));

    return d;
}

DISTMATR DISTMATRfile(FILE* file, DISTMATR d) {
    int i, j;

    for (i = 0; i < d->N; i++)
        for (j = 0; j < d->N; j++)
            fscanf(file, "%d", &(d->m[i][j]));
    
    return d;
}

int DISTMATRgetN(DISTMATR d) {
    return d->N;
}

int DISTMATRgetVal(DISTMATR d, int i, int j) {
    return d->m[i][j];
}