#include "ingrediente.h"

static ingrediente_t *leggiIngrediente(FILE *in);
static void stampaIngrediente(ingrediente_t *ing, FILE *out);

static link newNode(ingrediente_t *i, link next) {
  link x = malloc(sizeof *x);
  if (x==NULL)
    return NULL;
  x->ing = i;
  x->next = next;
  return x;
}

static void listInsTail(list *I, ingrediente_t *i) {
  if (I == NULL)
    return;
  if (I->head == NULL) {
    I->head = I->tail = newNode(i, NULL);
  } else {
    I->tail->next = newNode(i, NULL);
    I->tail = I->tail->next;
  }
}

list *leggiIngredienti(FILE *fin) {
  int i;
  list *ingredienti;
  ingrediente_t *ing;

  ingredienti = calloc(1, sizeof(list));
  if (ingredienti == NULL)
    return NULL;

  fscanf(fin, "%d", &ingredienti->nIngr);
  for (i=0; i<ingredienti->nIngr; i++) {
    ing = leggiIngrediente(fin);
    listInsTail(ingredienti, ing);
  }
  return ingredienti;
}

static ingrediente_t *leggiIngrediente(FILE *in) {
  ingrediente_t *ing;
  char nomeTmp[LEN];
  float prezzo, cal;

  ing = calloc(1, sizeof(ingrediente_t));
  fscanf(in, "%s %f %f", nomeTmp, &prezzo, &cal);
  ing->nome = strdup(nomeTmp);
  ing->prezzo = prezzo;
  ing->cal = cal;
  return ing;
}

ingrediente_t *cercaIngrediente(char *nomeIngr, list *ingredienti) {
  link t;
  if (ingredienti == NULL || ingredienti->head == NULL)
    return NULL;
  t = ingredienti->head;
  while(t != NULL) {
    if (strcmp(nomeIngr, t->ing->nome) == 0)
      return t->ing;
    t = t->next;
  }
  return NULL;
}

void stampaIngredienti(list *ingredienti, FILE *out) {
  link t;
  if (ingredienti == NULL || ingredienti->head == NULL)
    return;
  t = ingredienti->head;
  printf("\n");
  while(t != NULL) {
    stampaIngrediente(t->ing, out);
    t = t->next;
  }
  printf("\n\n");
}

static void stampaIngrediente(ingrediente_t *ing, FILE *out) {
	fprintf(out, "%s %.2f e/Kg %.2f cal/g\n", ing->nome, ing->prezzo, ing->cal);
}

static void liberaIngrediente(ingrediente_t *ing) {
  if (ing == NULL) return;
  if (ing->nome) free(ing->nome);
  free(ing);
}

void liberaIngredienti(list *ingredienti) {
  link t, delete;
  if (ingredienti == NULL || ingredienti->head == NULL)
    return;
  t = ingredienti->head, delete = NULL;
  printf("\n");
  while(t != NULL) {
    delete = t;
    liberaIngrediente(t->ing);
    t = t->next;
    free(delete);
  }
  free(ingredienti);
  printf("\n\n");

}
