#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "catArray.h"

typedef struct categoria_s {
  char* nome;
} categoria_t;

struct categorie_s {
  int nCategorie;
  int dimVett;
  categoria_t *vc;
};

catArray_t catArrayInit() {
  catArray_t c = calloc(1, sizeof(*c));
  c->nCategorie = 0;
  c->dimVett = 0;
  c->vc = NULL;
  return c;
}

void stampaCategoria(catArray_t c, int index) {
  if (c == NULL) return;
  if (c->vc == NULL) return;
  printf("%s\n", c->vc[index].nome);
}

int categorieGetNum(catArray_t c) {
  if (c == NULL) return 0;
  return c->nCategorie;
}

int categorieCercaOAggiungi(catArray_t categorie, char *cat) {
  if (categorie == NULL) return -1;
  int k = 0;
  while (k < categorie->nCategorie && strcmp(categorie->vc[k].nome, cat) != 0)
    k++;
  if ( k == categorie->nCategorie) { //categoria non trovata (primo elemento per tale categoria)
    if (categorie->dimVett == 0) {
			categorie->dimVett = 1;
			categorie->vc = calloc (categorie->dimVett, sizeof(categoria_t));
    } else if (categorie->nCategorie == categorie->dimVett) {
      categorie->dimVett *= 2;
      categorie->vc = realloc (categorie->vc, categorie->dimVett*sizeof(categoria_t));
    }
    categorie->vc[k].nome = strdup(cat);
    categorie->nCategorie++;
  }
  return k;
}

void freeCategorie(catArray_t categorie) {
  int i;
	if (categorie == NULL) return;
	if (categorie->vc == NULL) return;
  for(i = 0; i < categorie->nCategorie; i++)
    free(categorie->vc[i].nome);
  free(categorie->vc);
}

