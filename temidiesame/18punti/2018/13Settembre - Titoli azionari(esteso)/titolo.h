#ifndef TITOLO_H
#define TITOLO_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "quotazione.h"

typedef struct titolo_ *titolo;

char *getKey(titolo t);
titolo titoloNEW(char *cod);
void titoloStore(FILE *out, titolo t);
int titolocmp(char *t1, char *t2);
quotazione ricercaQuotazione(titolo t, data_t d);
void titoloInsertTransazione(titolo t, data_t d, float val, int qta);
void titolominMaxRange(titolo t, float *min, float *max, data_t d1, data_t d2);
void titoloMinMax(titolo t, float *min, float *max);
void titolobilancia(titolo t, int s);
#endif