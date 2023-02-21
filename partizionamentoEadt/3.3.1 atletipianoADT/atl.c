#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "atl.h"

void stampaAtleta(atl_t a, catArray_t categorie, esArray_t esercizi, FILE *fp) {
  fprintf(fp, "%s, %s, %s, %d/%d/%d, %d, ", a->codice, a->cognome, a->nome,  a->data.giorno, a->data.mese, a->data.anno, a->ore);
  stampaCategoria(categorie, a->categoria);
  if (a->piano != NULL) stampaPiano(stdout, esercizi, a->piano);
}

void atletaAggiornaOre(atl_t a) {
  if (a == NULL) return;
  printf("Inserire il nuovo monte ore settimanale: ");
  scanf("%d", &a->ore);
}

void caricaPiano(atl_t atleta, esArray_t esercizi) {
  FILE *in = NULL;
  char filename[50];
  strcpy(filename, atleta->codice);
  strcat(filename, ".txt");
  if ((in = fopen(filename, "r")) == NULL) {
    printf("Piano di allenamento non disponibile\n");
    return;
  }

  atleta->piano = esListCaricaPiano(in, esercizi);

#if DBG
  printf("Piano di allenamento per %s:\n", atleta->codice);
  stampaPiano(stdout, atleta->piano);
#endif /* DBG */
}

void atletaGestionePiano(atl_t a, esArray_t e) {
  char filename[50];
  FILE *out;
  if (a == NULL) return;
  if (a->piano == NULL) caricaPiano(a, e);
  else {
    strcpy(filename, a->codice);
    strcat(filename, ".txt");
    out = fopen(filename, "w");
    stampaPiano(out, e, a->piano);
    fclose(out);
  }
}

void parsificaData(char strData[], data_t *data) {
	sscanf(strData, "%d/%d/%d", &data->giorno, &data->mese, &data->anno);
}

atl_t leggiAtleta(FILE *fp, catArray_t categorie) {
  char codiceTmp[LEN], nomeTmp[LEN], cognomeTmp[LEN], categoriaTmp[LEN], dataTmp[LEN];
  int ore;
  if (fscanf(fp, "%s %s %s %s %s %d", codiceTmp, cognomeTmp, nomeTmp, categoriaTmp, dataTmp, &ore) == 6) {
    atl_t a = calloc(1, sizeof(*a));
    a->codice = strdup(codiceTmp);
    a->nome = strdup(nomeTmp);
    a->cognome = strdup(cognomeTmp);
    a->categoria = categorieCercaOAggiungi(categorie, categoriaTmp);
    parsificaData(dataTmp, &(a->data));
    a->ore = ore;
    a->piano = NULL;
    return a;
  }
  return NULL;
}

void freeAtleta(atl_t a) {
	if (a == NULL) return;
  free(a->codice);
  free(a->nome);
  free(a->cognome);
  if (a->piano != NULL) freePiano(a->piano);
  free(a);
}
