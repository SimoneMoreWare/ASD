#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "atlList.h"

typedef struct nodoAtleta_s *linkAtleta;
typedef struct nodoAtleta_s {
  atl_t a;
  linkAtleta next;
} nodoAtleta_t;

struct atleti_s {
  int nAtleti;
  linkAtleta head, tail;
};

atlList_t atlListInit() {
  atlList_t a = calloc(1, sizeof(*a));
  a->head = a->tail = NULL;
  a->nAtleti = 0;
  return a;
}

static linkAtleta newNodoAtleta(atl_t a, linkAtleta next) {
	linkAtleta n = calloc(1, sizeof(*n));
	if (n == NULL) return NULL;
	n->a = a;
	n->next = next;
	return n;
}

void inserisciInListaAtleti(atlList_t A, atl_t a) {
	linkAtleta toBeAdded = newNodoAtleta(a, NULL);
	if (toBeAdded == NULL) return;
    if(A->head == NULL) {
      A->head = A->tail = toBeAdded;
    } else {
      A->tail->next = toBeAdded;
      A->tail = toBeAdded;
    }
}

void stampaAnagrafica(atlList_t atleti, catArray_t categorie, esArray_t esercizi, char *file) {
  FILE *fp;
  if(file == NULL)
      fp = stdout;
  else
      fp = fopen(file,"w");

  linkAtleta iter = NULL;
  for(iter = atleti->head;iter != NULL; iter=iter->next) {
    stampaAtleta(iter->a, categorie, esercizi, fp);
  }

  if(file!=NULL)
    fclose(fp);
}

atl_t ricercaCodice(atlList_t atleti, char* codice){
  linkAtleta iter;
  for(iter = atleti->head; iter != NULL; iter=iter->next) {
    if (strcmp(iter->a->codice, codice) == 0) {
      return iter->a;
    }
  }
  return NULL;
}

void ricercaCognome(atlList_t atleti, catArray_t categorie, esArray_t esercizi, char* cognome, int nCharConfronto){
  linkAtleta iter;
  int len = strlen(cognome);
  for(iter = atleti->head; iter != NULL; iter=iter->next) {
    if (strncmp(iter->a->cognome, cognome, len) == 0) stampaAtleta(iter->a, categorie, esercizi, stdout);
  }
}

void stampaPerCategoria(atlList_t atleti, catArray_t categorie, esArray_t esercizi){
	int i, n = categorieGetNum(categorie);
	for(i=0;i<n;i++){
		stampaCategoria(categorie, i);
		linkAtleta iter;
		for(iter = atleti->head; iter != NULL; iter=iter->next) {
      if (iter->a->categoria == i)
			stampaAtleta(iter->a, categorie, esercizi, stdout);
		}
	}
}

void caricaAnagrafica(atlList_t atleti, catArray_t categorie, char *file){

  if (atleti == NULL) return;
  if (categorie == NULL) return;

  FILE *fp;
  fp = fopen(file,"r");

  if(fp == NULL) {
		printf("Errore nell'apertura del file\n ");
		exit(-1);
  }

  atl_t a = NULL;
  while((a = leggiAtleta(fp, categorie)) != NULL) {
    inserisciInListaAtleti(atleti, a);
  }
  fclose(fp);
}

void aggiungi(atlList_t atleti, catArray_t categorie){
  printf("Cod Cogn Nome Cat Data Ore: ");
  atl_t a = leggiAtleta(stdin, categorie);
  if (a != NULL) inserisciInListaAtleti(atleti, a);
}

void elimina(atlList_t atleti, char* codice){
  linkAtleta iter, prev;
  for(iter = atleti->head, prev = NULL; iter != NULL; prev = iter, iter=iter->next) {
    if (strcmp(iter->a->codice, codice) == 0) {
	  if (iter == atleti->head && iter == atleti->tail) {
		  atleti->head = atleti->tail = NULL;
	  } else if (iter == atleti->head) {
		atleti->head = iter->next;
	  } else if (iter == atleti->tail) {
		atleti->tail = prev;
		prev->next = NULL;
	  } else {
		 prev->next = iter->next;
	  }
	  free(iter);
      break;
    }
  }
}

void freeAtleti(atlList_t atleti) {
  linkAtleta iter, toBeDeleted;
  for(iter = atleti->head; iter != NULL; ) {
    toBeDeleted = iter;
    iter=iter->next;
    freeAtleta(toBeDeleted->a);
    free(toBeDeleted);
  }
}
