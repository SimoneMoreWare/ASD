#ifndef ELENCO_H
#define ELENCO_H
#include <stdio.h>
#include <stdlib.h>

typedef struct elenco_t *ELENCO;

ELENCO ELENCOinit(int maxN);
ELENCO ELENCOfile(FILE* file);
int ELENCOgetN(ELENCO e);

#endif