#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "BST.h"

typedef struct BSTnode* link;
struct BSTnode { char *key; int index; link l; link  r; } ;

struct binarysearchtree { link root; int N; link z; };

static link NEWtree_node(char *key, int index, link l, link r);
static void deleteR(link h, link z);
static link insertR(link h, char *key, int i, link z);
static int  searchR(link h, char *key, link z);

static link NEWtree_node(char *key, int index, link l, link r) {
  link x = malloc(sizeof *x);
  if (x == NULL) {
    printf("Errore di allocazione di memoria\n");
    exit(1);
  }
  x->key = strdup(key);
  x->index = index;
  x->l = l;
  x->r = r;
  return x;
}

BST BSTinit( ) {
  BST bst = malloc(sizeof *bst) ;
  if (bst == NULL) {
    printf("Errore di allocazione di memoria\n");
    exit(1);
  }
  bst->N = 0;
  bst->root = bst->z = NULL;
  return bst;
}

static void deleteR(link r, link z) {
  if (r == z)
    return;
  deleteR(r->l, z);
  deleteR(r->r, z);
  free(r->key);
  free(r);
}

void BSTfree(BST bst) {
  deleteR(bst->root, bst->z);
  free(bst);
}

int BSTempty(BST bst) {
  return (bst==NULL || bst->N==0);
}

int BSTcount(BST bst) {
  if (BSTempty(bst))
    return 0;
  return bst->N;
}

static link insertR(link h, char *key, int i, link z) {
  if (h == z)
    return NEWtree_node(key, i, z, z);
  if (strcmp(key, h->key) < 0) {
    h->l = insertR(h->l, key, i, z);
  }
  else {
    h->r = insertR(h->r, key, i, z);
  }
  return h;
}

void BSTinsert(BST bst, char *str, int i) {
  bst->root = insertR(bst->root, str, i, bst->z);
  bst->N++;
}

static int searchR(link h, char *key, link z) {
  int result;
  if (h == z)
    return -1;
  if (strcmp(key, h->key)==0)
    return h->index;
  result = searchR(h->l, key, z);
  if (result != -1)
    return result;
  result = searchR(h->r, key, z);
  return result;
  }

int BSTsearch(BST bst, char *key) {
  if (BSTempty(bst))
    return -1;
  return searchR(bst->root, key, bst->z);
}


