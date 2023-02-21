#ifndef ESERCIZI_H_DEFINED
#define ESERCIZI_H_DEFINED

#include <stdio.h>
#include "es.h"

typedef struct esercizi_s* esArray_t;

esArray_t esArrayInit();
void stampaEsercizioVett(esArray_t esercizi, int index);
int cercaEsercizio(char *esercizio, esArray_t esercizi);
void stampaEsercizi(esArray_t esercizi, char* file);
void caricaEsercizi(esArray_t esercizi, char *file);
void freeEsercizi(esArray_t esercizi);

#endif
