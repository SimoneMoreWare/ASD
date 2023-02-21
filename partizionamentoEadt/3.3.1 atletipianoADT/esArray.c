#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "esArray.h"

struct esercizi_s {
  int nEsercizi;
  int dimVett;
  es_t *ve;
};

esArray_t esArrayInit() {
  esArray_t e = calloc(1, sizeof(*e));
  if (e == NULL) return NULL;
  e->nEsercizi = 0;
  e->dimVett = 0;
  e->ve = NULL;
  return e;
}

void stampaEsercizioVett(esArray_t esercizi, int index) {
  if (esercizi == NULL) return;
  if (esercizi->ve == NULL) return;
  stampaEsercizio(esercizi->ve[index]);
}

int cercaEsercizio(char *esercizio, esArray_t esercizi) {
  int i;
  if (esercizi == NULL) return -1;
  for(i=0;i<esercizi->nEsercizi;i++) {
    if(!strcmp(esercizio, esercizi->ve[i]->nomeEs)) return i;
  }
  return -1;
}

void stampaEsercizi(esArray_t esercizi, char* file) {
  int i;
  FILE *fp;

  if (esercizi == NULL) return;
  if(file == NULL)
      fp = stdout;
  else
      fp = fopen(file,"w");

  for(i=0;i<esercizi->nEsercizi;i++) {
    stampaEsercizio(esercizi->ve[i]);
  }
  if(file!=NULL)
    fclose(fp);
}

void caricaEsercizi(esArray_t esercizi, char *file){
  FILE *fp;
  int i = 0;

  if (esercizi == NULL) return;

  fp = fopen(file,"r");

  if(fp == NULL) {
		printf("Errore nell'apertura del file\n ");
		exit(-1);
  }

  fscanf(fp, "%d\n", &esercizi->nEsercizi);
  esercizi->ve = calloc(esercizi->nEsercizi, sizeof(es_t));
  esercizi->dimVett = esercizi->nEsercizi;

  es_t e = NULL;
  i = 0;
  while(i < esercizi->dimVett && (e = leggiEsercizio(fp)) != NULL) esercizi->ve[i++] = e;
  fclose(fp);
}

void freeEsercizi(esArray_t esercizi) {
	int i;
	if (esercizi == NULL) return;
	if (esercizi->ve != NULL) {
		for(i=0;i<esercizi->nEsercizi;i++) {
		  freeEsercizio(esercizi->ve[i]);
		}
	  free(esercizi->ve);
	}
}

