#ifndef CATEGORIE_H_DEFINED
#define CATEGORIE_H_DEFINED

#include <stdio.h>

typedef struct categorie_s* catArray_t;

catArray_t catArrayInit();
void stampaCategoria(catArray_t c, int index);
int categorieGetNum(catArray_t c);
int categorieCercaOAggiungi(catArray_t c, char *cat);
void freeCategorie(catArray_t c);
#endif
