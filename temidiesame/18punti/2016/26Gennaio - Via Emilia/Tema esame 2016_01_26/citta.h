#ifndef CITTA_H_INCLUDED
#define CITTA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 21

typedef struct{
   char nome[MAX];
   int abitanti, distanzaInizio;
}Citta;

typedef enum{UGUALE, DIVERSO}Simboli;

Citta CITTAread(FILE *f);
void CITTAprint(Citta c, FILE *f);
Simboli CITTAcompare(Citta c1, Citta c2);

#endif // CITTA_H_INCLUDED
