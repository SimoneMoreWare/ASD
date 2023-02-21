#ifndef ESERCIZIO_H_DEFINED
#define ESERCIZIO_H_DEFINED

#include <stdio.h>

#define LEN 50

typedef struct esercizio_s* es_t;

struct esercizio_s {
  char *nomeEs;
  char *tipoEs;
  char *catEs;
};

void stampaEsercizio(es_t e);
void freeEsercizio(es_t e);
es_t leggiEsercizio(FILE *fp);

#endif
