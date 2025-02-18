#include "SERVIZI.h"

typedef struct servizi_t {
    int *reach;
    int maxN;
    int N;
    float media;
} *SERVIZI;

// dimenticato tipo di ritorno
SERVIZI SERVIZIinit(int maxN, float media) {
    SERVIZI s = (SERVIZI) malloc(sizeof(*s));
    
    s->maxN = maxN;
    s->N = 0;
    s->reach = (int*) malloc(s->maxN * sizeof(int));
    s->media = media;

    return s;
}

SERVIZI SERVIZIfile(FILE* file) {
    int i, maxN, N;
    float media;
    SERVIZI s;

    fscanf(file, "%d %d %f", &maxN, &N, &media);
    s = SERVIZIinit(maxN, media);
    s->N = N;
    for (i = 0; i < s->maxN; i++)
        fscanf(file, "%d", &(s->reach[i]));

    return s;
}

int SERVIZIgetMaxN(SERVIZI s) {
    return s->maxN;
}

int SERVIZIgetN(SERVIZI s) {
    return s->N;
}

// dimenticato tipo di ritorno
int SERVIZIcount(SERVIZI s, int i) {
    int j, n = 0;

    for (j = 0; j < s->maxN; j++)
        if (i != j && s->reach[j] == i)
            n++;
    
    return n;
}

int SERVIZIgetReachVal(SERVIZI s, int i) {
    return s->reach[i];
}

// rimossi SEDI *M e int N
int checkPart(SERVIZI s, DISTMATR d, int MAXD, int MINS) {
    int i, j, k, curr;
    int *check = (int*) calloc(SERVIZIgetMaxN(s), sizeof(int));

    // dimenticate le {}
    for (i = 0; i < SERVIZIgetN(s); i++) {
        // modificata condizione check[j] != 0
        for (j = 0; j < DISTMATRgetN(d) && check[j] != 0; j++);
        curr = SERVIZIgetReachVal(s, j);
        for (k = 0; k < DISTMATRgetN(d); k++)
            // dimenticato un indice per la funzione DISTMATRgetVal
            if (curr == SERVIZIgetReachVal(s, k) && DISTMATRgetVal(d, k, curr) <= MAXD)
                check[k] = 1;
        if (SERVIZIcount(s, curr) < MINS)
            return 0;
    }

    return 1;
}