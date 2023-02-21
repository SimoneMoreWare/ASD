#ifndef ATLETA_H_DEFINED
#define ATLETA_H_DEFINED

#include <stdio.h>

#include "catArray.h"
#include "esArray.h"
#include "esList.h"

#define LEN 50

typedef struct atleta_s* atl_t;

typedef struct data_s{
  int giorno;
  int mese;
  int anno;
} data_t;

struct atleta_s {
  char* codice;
  char* cognome;
  char* nome;
  int categoria;
  data_t data;
  int ore;
  esList_t piano;
};

void stampaAtleta(atl_t a, catArray_t categorie, esArray_t esercizi, FILE *fp);
void atletaAggiornaOre(atl_t a);
void atletaGestionePiano(atl_t a, esArray_t e);
void freeAtleta(atl_t a);
atl_t leggiAtleta();


#endif
