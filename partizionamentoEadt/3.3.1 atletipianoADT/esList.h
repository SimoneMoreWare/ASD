#ifndef PIANO_H_DEFINED
#define PIANO_H_DEFINED

#include <stdio.h>

#include "esArray.h"

typedef struct piano_s* esList_t;

void stampaPiano(FILE *fp, esArray_t esercizi, esList_t p);
void freePiano(esList_t p);
esList_t esListCaricaPiano(FILE *fp, esArray_t esercizi);
void aggiornaEsercizioInPiano(esList_t p, esArray_t esercizi);

#endif
