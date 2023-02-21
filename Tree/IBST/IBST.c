#include <stdlib.h>
#include <stdio.h>
#include "Item.h"
#include "IBST.h"

typedef struct IBSTnode* link;
struct IBSTnode { Item item; link l; link r; int N; int max; } ;

struct intervalbinarysearchtree { link root; int size; link z; };

static link NEW(Item item, link l, link r, int N, int max);
static void treeFree(link h, link z);
static void NODEshow(link x);

static link NEW(Item item, link l, link r, int N, int max) {
  link x = malloc(sizeof *x);
  x->item = item;
  x->l = l;
  x->r = r;
  x->N = N;
  x->max = max;
  return x;
}

static void NODEshow(link x) {
  ITEMstore(x->item);
  printf("max = %d\n", x->max);
}

IBST IBSTinit( ) {
  IBST ibst = malloc(sizeof *ibst) ;
  ibst->size = 0;
  ibst->root = ( ibst->z = NEW(ITEMsetNull(), NULL, NULL, 0, -1));
  return ibst;
}

void IBSTfree(IBST ibst) {
  if (ibst == NULL)
    return;
  treeFree(ibst->root, ibst->z);
  free(ibst->z);
  free(ibst);
}

static void treeFree(link h, link z) {
  if (h == z)
    return;
  treeFree(h->l, z);
  treeFree(h->r, z);
  free(h);
}

int IBSTcount(IBST ibst) {
  return ibst->size;
}

int IBSTempty(IBST ibst) {
  if (IBSTcount(ibst) == 0)
    return 1;
  return 0;
}

Item searchR(link h, Item item, link z) {
  if (h == z)
    return ITEMsetNull();
  if (ITEMoverlap(item, h->item))
    return h->item;
  if (ITEMlt_int(item, h->l->max))
    return searchR(h->l, item, z);
  else
    return searchR(h->r, item, z);
  }

Item IBSTsearch(IBST ibst, Item item) {
  return searchR(ibst->root, item, ibst->z);
}

int max (int a, int b, int c) {
  int m = a;
  if (b > m)
    m = b;
  if (c > m)
    m = c;
  return m;
}

link insertR(link h, Item item, link z) {
  if (h == z)
    return NEW(item, z, z, 1, ITEMhigh(item));
  if (ITEMlt(item, h->item)) {
    h->l = insertR(h->l, item, z);
    h->max = max(h->max, h->l->max, h->r->max);
  }
  else {
    h->r = insertR(h->r, item, z);
    h->max = max(h->max, h->l->max, h->r->max);
  }
  (h->N)++;
  return h;
}

void IBSTinsert(IBST ibst, Item item) {
  ibst->root = insertR(ibst->root, item, ibst->z);
  ibst->size++;
}

link rotR(link h) {
  link x = h->l;
  h->l = x->r;
  x->r = h;
  x->N = h->N;
  h->N = h->r->N + h->l->N +1;
  h->max = max(ITEMhigh(h->item), h->l->max, h->r->max);
  x->max = max(ITEMhigh(x->item), x->l->max, x->r->max);
  return x;
}

link rotL(link h) {
  link x = h->r;
  h->r = x->l;
  x->l = h;
  x->N = h->N;
  h->N = h->l->N + h->r->N +1;
  h->max = max(ITEMhigh(h->item), h->l->max, h->r->max);
  x->max = max(ITEMhigh(x->item), x->l->max, x->r->max);
  return x;
}

static void treePrintR(link h, link z, int strategy) {
  if (h == z)
    return;

  if (strategy == PREORDER)
    NODEshow(h);
  treePrintR(h->l, z, strategy);
  if (strategy == INORDER)
    NODEshow(h);
  treePrintR(h->r, z, strategy);
  if (strategy == POSTORDER)
    NODEshow(h);
}

void IBSTvisit(IBST ibst, int strategy) {
  if (IBSTempty(ibst))
    return;
  treePrintR(ibst->root, ibst->z, strategy);
}

link partR(link h, int r) {
  int t  = h->l->N;
  if ( t > r) {
    h->l = partR(h->l, r);
    h = rotR(h);
  }
  if ( t < r) {
    h->r = partR(h->r, r-t-1);
    h = rotL(h);
  }
  return h;
}

link joinLR(link a, link b, link z) {
  if (b == z)
    return a;
  b = partR(b, 0);
  b->l = a;
  b->N = a->N + b->r->N +1;
  b->max = max(ITEMhigh(b->item), a->max, b->r->max);
  return b;
}

link deleteR(link h, Item item, link z) {
  link x;
  if (h == z)
    return z;
  if (ITEMlt(item, h->item)) {
    h->l = deleteR(h->l, item, z);
    h->max = max(ITEMhigh(h->item), h->l->max, h->r->max);
  }
  if (ITEMlt(h->item, item)) {
    h->r = deleteR(h->r, item, z);
    h->max = max(ITEMhigh(h->item), h->l->max, h->r->max);
  }
  (h->N)--;
  if (ITEMeq(item, h->item)) {
    x = h;
    h = joinLR(h->l, h->r, z);
    free(x);
  }
  return h;
}

void IBSTdelete(IBST ibst, Item item) {
  ibst->root = deleteR(ibst->root, item, ibst->z);
  ibst->size--;
}
