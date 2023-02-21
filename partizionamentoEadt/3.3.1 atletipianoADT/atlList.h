#ifndef ATLETI_H_DEFINED
#define ATLETI_H_DEFINED

#include <stdio.h>

#include "atl.h"

typedef struct atleti_s* atlList_t;

atlList_t atlListInit();
void stampaAnagrafica(atlList_t atleti, catArray_t categorie, esArray_t esercizi, char *file);
atl_t ricercaCodice(atlList_t atleti, char *codice);
void stampaPerCategoria(atlList_t atleti, catArray_t categorie, esArray_t esercizi);
void caricaAnagrafica(atlList_t atleti, catArray_t categorie, char *file);
void elimina(atlList_t atleti, char* codice);
void ricercaCognome(atlList_t atleti, catArray_t categorie, esArray_t esercizi, char* cognome, int nCharConfronto);
void aggiungi(atlList_t atleti, catArray_t categorie);
void freeAtleti(atlList_t atleti);
#endif
