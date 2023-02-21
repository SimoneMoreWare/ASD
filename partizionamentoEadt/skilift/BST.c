#include <stdlib.h>
#include <stdio.h>
#include "skilift.h"
#include "ST.h"
#include "skier.h"
#include "BST.h"

typedef struct BSTnode* link;

struct BSTnode {
  skier item;
  link l;
  link r;
};

struct binarysearchtree {
  link root;
  link z;
};

static void treeFree(link h, link z);
static void treeDestroy(link h, link z);
static int countR(link h, link z);
static link NEW(skier item, link l, link r);
static skier searchR(link h, int k, link z);
static link insertR(link h, skier x, link z);
static void tree_print(link h, link z, FILE *fp);

static link NEW(skier item, link l, link r) {
  link x = malloc(sizeof *x);
  x->item = item; x->l = l; x->r = r;
  return x;
}

BST BSTinit( ) {
  BST bst = malloc(sizeof *bst) ;
  bst->root=(bst->z=NEW(SKIERNULL(), NULL, NULL));
  return bst;
}

void BSTfree(BST bst) {
  if (bst == NULL)
    return;
  treeFree(bst->root, bst->z);
  SKIERfree(bst->z->item);
  free(bst->z);
  free(bst);
}

static void treeFree(link h, link z) {
  if (h == z) return;
  treeFree(h->l, z);
  treeFree(h->r, z);
  free(h);
}

void BSTdestroy(BST bst) {
  if (bst == NULL)
    return;
  treeDestroy(bst->root, bst->z);
  SKIERfree(bst->z->item);
  free(bst->z);
  free(bst);
}

static void treeDestroy(link h, link z) {
  if (h == z) return;
  treeDestroy(h->l, z);
  treeDestroy(h->r, z);
  SKIERfree(h->item);
  free(h);
}

static int countR(link h, link z) {
  if (h == z)
    return 0;
  return countR(h->l, z) + countR(h->r, z) + 1;
}

int BSTcount(BST bst) {
  return countR(bst->root, bst->z);
}

int BSTempty(BST bst) {
  return BSTcount(bst) == 0;
}

skier BSTsearch(BST bst, int k) {
  return searchR(bst->root, k, bst->z);
}

static skier searchR(link h, int k, link z) {
  skier result = SKIERNULL();
  if (h == z)
    return result;
  if (k == SKIERid(h->item))
    return h->item;
  if (k < SKIERid(h->item))
    return searchR(h->l, k, z);
  return searchR(h->r, k, z);
}

void BSTinsert(BST bst, skier x) {
  bst->root = insertR(bst->root, x, bst->z);
}

static link insertR(link h, skier x, link z) {
  if (h == z)
    return NEW(x, z, z);
  if (SKIERid(x) < SKIERid(h->item))
    h->l = insertR(h->l, x, z);
  else
    h->r = insertR(h->r, x, z);
  return h;
}

void BSTprint(BST bst, FILE *fp) {
  tree_print(bst->root, bst->z, fp);
}

static void tree_print(link h, link z, FILE *fp) {
  if (h==z) return;
  tree_print(h->l, z, fp);
  SKIERprint(fp, h->item);
  tree_print(h->r, z, fp);
}
