#ifndef E1_TITOLI_H
#define E1_TITOLI_H

#include "titolo.h"

typedef struct titoli_ *titoli;

titoli titoliInit();
int listempty(titoli t);
void titoliFree(titoli t);
void titoliInsert(titoli list, titolo t);
titolo titoliSearch(titoli list, char *cod);
void titoliStore(FILE *out, titoli list);
#endif //E1_TITOLI_H
