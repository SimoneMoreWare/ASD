#include "ELENCO.h"

#define MAX_LEN 30

typedef struct elenco_t {
    char **citta; // modificato per essere matrice di stringhe
    int maxN;
} *ELENCO;

ELENCO ELENCOinit(int maxN) {
    int i;
    ELENCO e = (ELENCO) malloc(sizeof(*e));

    e->maxN = maxN;
    e->citta = (char**) malloc(sizeof(char*));
    for (i = 0; i < e->maxN; i++)
        e->citta[i] = (char*) malloc(MAX_LEN * sizeof(char));
    
    return e;
}

ELENCO ELENCOfile(FILE* file) {
    int i, maxN;
    ELENCO e;

    fscanf(file, "%d", &maxN);
    e = ELENCOinit(maxN);
    for (i = 0; i < e->maxN; i++)
        fscanf(file, "%s", e->citta[i]);

    return e;
}

int ELENCOgetN(ELENCO e) {
    return e->maxN;
}