#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "es.h"

void stampaEsercizio(es_t e) {
  if (e == NULL) return;
  printf("%s %s %s\n", e->nomeEs, e->catEs, e->tipoEs);
}

void freeEsercizio(es_t e) {
  if (e == NULL) return;
  free(e->nomeEs);
  free(e->catEs);
  free(e->tipoEs);
  free(e);
}

es_t leggiEsercizio(FILE *fp) {
  if (fp == NULL) return NULL;
  es_t e = calloc(1, sizeof(*e));
  if (e == NULL) return NULL;
  char nomeTmp[LEN], catTmp[LEN], tipoTmp[LEN];
  if (fscanf(fp, "%s %s %s\n", nomeTmp, catTmp, tipoTmp) == 3) {
      e->catEs = strdup(catTmp);
      e->nomeEs = strdup(nomeTmp);
      e->tipoEs = strdup(tipoTmp);
      return e;
  } else {
    free(e);
  }
  return NULL;
}
