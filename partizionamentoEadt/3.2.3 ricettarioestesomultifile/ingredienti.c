#include "ingredienti.h"
#include "ricette.h"

tabIngr *leggiIngredienti(FILE *in) {
  int i;
  tabIngr *ingredienti = calloc(1, sizeof(tabIngr));
  if (ingredienti == NULL)
    return NULL;
  fscanf(in, "%d", &ingredienti->nIngr);
  ingredienti->vettIng = calloc(ingredienti->nIngr, sizeof(ingrediente));
  if (ingredienti->vettIng == NULL)
    return NULL;
  for (i=0; i<ingredienti->nIngr; i++)
    leggiIngrediente(in, &(ingredienti->vettIng[i]));
  return ingredienti;
}

void leggiIngrediente(FILE *in, ingrediente *ing) {
  char nomeTmp[LEN];
  float prezzo, cal;
  fscanf(in, "%s %f %f", nomeTmp, &prezzo, &cal);
  ing->nome = strdup(nomeTmp);
  if (ing->nome == NULL)
    exit(-1);
  ing->prezzo = prezzo;
  ing->cal = cal;
  ing->head = ing->tail = NULL;
}

ingrediente *cercaIngrediente(char *nomeIngr, tabIngr *ingredienti) {
  int i;
  if (ingredienti == NULL || ingredienti->vettIng == NULL)
    return NULL;
  for (i=0; i<ingredienti->nIngr; i++)
    if (strcmp(nomeIngr, ingredienti->vettIng[i].nome) == 0)
      return &(ingredienti->vettIng[i]);
  return NULL;
}

void stampaIngredienti(tabIngr *ingredienti, FILE *out) {
  int i;
  if (ingredienti == NULL || ingredienti->vettIng == NULL)
    return;
  for (i=0; i<ingredienti->nIngr; i++)
    stampaIngrediente(ingredienti->vettIng[i], out);
  printf("\n\n");
}

void stampaIngrediente(ingrediente ing, FILE *out) {
 fprintf(out, "%s %.2f e/Kg %.2f cal/g\n", ing.nome, ing.prezzo, ing.cal);
}

void stampaRicetteIngrediente(ingrediente ing, FILE *out) {
  elenco *iter = ing.head;
  while (iter != NULL) {
    printf("%s\n", iter->r->nomeRicetta);
    iter = iter->next;
  }
}

void liberaElenco(ingrediente ing) {
  elenco *iter = ing.head;
  elenco *app;
  while (iter != NULL) {
    app = iter;
    iter = iter->next;
    free(app);
  }
}

void liberaIngredienti(tabIngr *ingredienti) {
  int i; 
  if (ingredienti == NULL )
    return;
  for (i=0; i<ingredienti->nIngr; i++) {
    free(ingredienti->vettIng[i].nome);
    liberaElenco(ingredienti->vettIng[i]);
  }
  free(ingredienti->vettIng);
  free(ingredienti);
  printf("\n\n");

}
