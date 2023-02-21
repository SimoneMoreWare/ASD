#ifndef RICETTE_H_DEFINED
#define RICETTE_H_DEFINED

#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#include "ingredienti.h"

typedef struct rIng_ {
  int qta;
  struct rIng_ *next;
  ingrediente *ing;
} rIng;

typedef struct ricetta_ {
  int tempo;
  int nIngr;
  char *nomeRicetta;
  float costo, cal;
  rIng *head, *tail;
  struct ricetta_ *next;
} ricetta;

typedef struct tabRicette {
  ricetta *head, *tail;
  int nRicette;
} tabRicette;

ricetta *leggiRicetta(FILE *in, tabIngr* ingredienti);
ricetta *cercaRicetta(char *nomeRicetta, tabRicette *ricette);
tabRicette *leggiRicette(FILE *in, tabIngr* ingredienti);
void nuovaRicetta(tabRicette *ricette, tabIngr *ingredienti);
void stampaRicetta(ricetta *ric, FILE *out);
void stampaRicette(tabRicette *ricette, FILE *out);
void liberaRicette(tabRicette *ricette);
void liberaRicetta(ricetta *ric);

#endif
