#include "list.h"

typedef struct nodo_s {
  int val;
  struct nodo_s *next;
} nodo_t;

struct lista_s {
  int num;
  nodo_t *head;
  nodo_t *tail;
};

static nodo_t *newNodo(int val, nodo_t *next) {
  nodo_t *n = calloc(1, sizeof(nodo_t));
  if (n == NULL) return NULL;
  n->val = val;
  n->next = next;
  return n;
}

lista_t LISTAinit() {
  lista_t l = calloc(1, sizeof(*l));
  if (l == NULL) return NULL;
  l->head = l->tail = NULL;
  l->num = 0;
  return l;
}

void LISTAinsert(lista_t l, int v) {
  if (l == NULL) return;
  nodo_t *n = newNodo(v, NULL);
  l->num++;
  if (l->head == NULL) { l->head = l->tail = n; return; }
  l->tail->next = n;
  l->tail = n;
}

int LISTAnum(lista_t l) {
  return l->num;
}

void LISTAshow(lista_t l) {
  nodo_t *x;
  if (l == NULL) return;
  for(x = l->head; x != NULL; x = x->next) {
    printf("%d ", x->val);
  }
  printf("\n");
}

void LISTAshowConNomi(lista_t l, TS ts) {
  nodo_t *x;
  if (l == NULL) return;
  for(x = l->head; x != NULL; x = x->next) {
    printf("%s ", TSleggi(ts, x->val));
  }
  printf("\n");
}

void LISTA2vett(lista_t l, int *v) {
  int i;
  nodo_t *x;
  if (l == NULL) return;
  for(i=0, x=l->head; x != NULL; i++, x = x->next) 
    v[i] = x->val ;
}

void LISTAfree(lista_t l) {
  nodo_t *x, *t;
  if (l == NULL) return;
  for(x = l->head; x != NULL; x = t) {
    t = x->next;
    free(x);
  }
  free(l);
}

