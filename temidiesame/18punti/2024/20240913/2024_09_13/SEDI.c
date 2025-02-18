#include "SEDI.h"

typedef struct sedi_t {
    int *s;
    int numS;
    int N;
    // eliminato DISTMATR, non necessario
} *SEDI;

SEDI SEDIinit(int maxN) {
    SEDI s = (SEDI) malloc(sizeof(*s));
    
    s->N = maxN;
    s->s = (int*) malloc(s->N * sizeof(int));
    s->numS = 0;

    return s;
}

SEDI SEDIfile(FILE* file) {
    int i, maxN;
    SEDI s;

    fscanf(file, "%d", &maxN);
    s = SEDIinit(maxN);
    fscanf(file, "%d", &(s->numS));
    for (i = 0; i < maxN; i++)
        fscanf(file, "%d", &(s->s[i]));

    return s;
}

int SEDIgetN(SEDI s) {
    return s->N;
}

int SEDIgetNumS(SEDI s) {
    return s->numS;
}

int SEDIisSede(SEDI s, int i) {
    return s->s[i];
}