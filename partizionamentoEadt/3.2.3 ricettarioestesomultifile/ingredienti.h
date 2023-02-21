#ifndef INGREDIENTI_H_DEFINED
#define INGREDIENTI_H_DEFINED
#define LEN 256

#include<string.h>
#include<stdlib.h>
#include<stdio.h>

typedef struct elenco_ {
  struct ricetta_ *r;
  struct elenco_ *next;
} elenco;

typedef struct {
	char *nome;
	float prezzo;
	float cal;
  elenco *head, *tail;
} ingrediente;


typedef struct tabIngr {
  ingrediente *vettIng;
  int nIngr;
} tabIngr;

void leggiIngrediente(FILE *in, ingrediente *ing);
tabIngr *leggiIngredienti(FILE *in);
void stampaIngrediente(ingrediente ing, FILE *out);
void stampaRicetteIngrediente(ingrediente ing, FILE *out);
void stampaIngredienti(tabIngr *ingredienti, FILE *out);
ingrediente *cercaIngrediente(char *nomeIngr, tabIngr *ingredienti);
void liberaIngredienti(tabIngr *ingredienti);

#endif
