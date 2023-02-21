#include "ricette.h"

ricetta *leggiRicetta(FILE *in, tabIngr* ingredienti) {
  int tempo, ni, i, qta;
  float costo = 0, cal = 0;
  char nomeR[LEN], nomeI[LEN];
  ricetta *r = calloc(1, sizeof(ricetta));
  rIng *ing;
  elenco *el;

  if (r == NULL)
    return NULL;
  if (in == stdin)
    printf("Inserire <nomeRicetta> <tempo> <numIngr>\n");
  fscanf(in, "%s %d %d", nomeR, &tempo, &ni);
  r->nomeRicetta = strdup(nomeR);
  r->tempo = tempo;
  r->nIngr = ni;
  for (i=0; i<ni; i++) {
    if (in == stdin)
      printf("Inserire <nomeIngrediente> <qta>\n");
    fscanf(in, "%s %d", nomeI, &qta);
    ing = calloc(1, sizeof(rIng));
    if (ing == NULL)
      return NULL;
    ing->ing = cercaIngrediente(nomeI, ingredienti);
    if (ing->ing == NULL) {
      free(ing);
      continue;
    }
    el = calloc(1, sizeof(elenco));
    if (el == NULL)
      exit(-1);
    el->r = r;
    if (ing->ing->head == NULL) {
      ing->ing->head = ing->ing->tail = el;
    } else {
      ing->ing->tail->next = el;
      ing->ing->tail = el;
    }
    ing->qta = qta;
    ing->next = NULL;
    if (ing->ing != NULL) {
      costo += (qta * ing->ing->prezzo / 1000.0) ;
      cal += (qta * ing->ing->cal ) ;
    }
    if (r->head == NULL) {
      r->head = r->tail = ing;
    } else {
      r->tail->next = ing;
      r->tail = ing;
    }
  }
  r->costo = costo;
  r->cal = cal;
  return r;
}

tabRicette *leggiRicette(FILE *in, tabIngr* ingredienti) {
  int i;
  ricetta *r;
  tabRicette *ricette = calloc(1, sizeof(tabRicette));
  if (ricette == NULL)
    return NULL;
  fscanf(in, "%d", &ricette->nRicette);
  for (i=0; i<ricette->nRicette; i++) {
    r = leggiRicetta(in, ingredienti);
    if (r == NULL)
      exit(-1);
    if (ricette->head == NULL) {
      ricette->head = ricette->tail = r;
    } else {
      ricette->tail->next = r;
      ricette->tail = r;
    }
  }
  return ricette;
}

ricetta *cercaRicetta(char *nomeRicetta, tabRicette *ricette) {
  ricetta *iter;
  if (ricette == NULL)
    return NULL;
  iter = ricette->head;
  while (iter != NULL && strcmp(iter->nomeRicetta, nomeRicetta))
    iter = iter->next;
  return iter;
}

void nuovaRicetta(tabRicette *ricette, tabIngr *ingredienti) {
  ricetta *r;
  if (ricette == NULL || ingredienti == NULL)
    return;
  r = leggiRicetta(stdin, ingredienti);
  if (r == NULL)
    exit(-1);
  if (ricette->head == NULL) {
    ricette->head = ricette->tail = r;
    return;
  }
  ricette->tail->next = r;
  ricette->tail = r;
  ricette->nRicette++;
}

void stampaRicetta(ricetta *ric, FILE *out) {
  if (ric == NULL) return;
  printf("%s\n", ric->nomeRicetta);
  rIng *iter = ric->head;
  while(iter != NULL) {
    printf("\t%s %d\n", iter->ing->nome, iter->qta);
    iter = iter->next;
  }
}

void stampaRicette(tabRicette *ricette, FILE *out) {
  if (ricette == NULL) return;
  ricetta *iter = ricette->head;
  while(iter != NULL) {
    stampaRicetta(iter, out);
    iter = iter->next;
  }
}

void liberaRicetta(ricetta *ric) {
  if (ric == NULL) return;
  free(ric->nomeRicetta);
  rIng *iter = ric->head;
  rIng *app;
  while(iter != NULL) {
    app = iter;
    iter = iter->next;
    free(app);
  }
}

void liberaRicette(tabRicette *ricette) {
  if (ricette == NULL) return;
  ricetta *iter = ricette->head;
  ricetta *app;
  while(iter != NULL) {
    app = iter;
    iter = iter->next;
    liberaRicetta(app);
    free(app);
  }
  free(ricette);
}
