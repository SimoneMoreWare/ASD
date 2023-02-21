#include <stdlib.h>
#include "stack.h"

typedef struct STACKnode* link;

struct STACKnode {
  int n;
  link next;
};

struct stack {  link top; int N; };

link NEW(int  n, link next) {
  link x = malloc(sizeof *x);
  x->n = n;
  x->next = next;
  return x;
}

S STACKinit(int MaxN) {
  S s = malloc(sizeof *s);
  s->top = NULL;
  s->N = 0;
  return s;
}

int STACKempty(S s) {
  return s->top == NULL;
}

int STACKsize(S s) {
  return s->N;
}

void STACKpush(S s, int n) {
  if (s->top == NULL) {
    s->top = NEW(n, s->top);
    (s->N)++;
    return;
  }
  s->top = NEW(n, s->top);
  (s->N)++;
}

int STACKpop(S s) {
  int n = s->top->n;
  link t = s->top->next;
  free(s->top);
  s->top = t;
  (s->N)--;
  return n;
}

int STACKtop(S s) {
  return s->top->n;
}

