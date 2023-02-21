#ifndef INGREDIENTE_H_DEFINED
#define INGREDIENTE_H_DEFINED
#define LEN 256

#include<string.h>
#include<stdlib.h>
#include<stdio.h>


typedef struct {
	char *nome;
	float prezzo;
	float cal;
} ingrediente_t;

typedef struct node *link;

struct node {
  ingrediente_t *ing;
  link next;
};


typedef struct {
  link head, tail;
  int nIngr;
} list;

list *leggiIngredienti(FILE *fin);
void stampaIngredienti(list *ingredienti, FILE *fout);
ingrediente_t *cercaIngrediente(char *nomeIngr, list *ingredienti);
void liberaIngredienti(list *ingredienti);

#endif
