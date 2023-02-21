#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "BST.h"

typedef struct BSTnode* link;
struct BSTnode { Item item; link l; link  r; } ;

struct binarysearchtree { link root; int N; link z; };

static link NEW(Item item, link l, link r);
static int count(link h, link z);
static Item searchR(link h, Item x, link z);
static link insertR(link h, Item x, link z);
static link rotR(link h);
static link rotL(link h);
static link insertT(link h, Item x, link z);
static Item minR(link h, link z);
static Item maxR(link h, link z);
static void tree_print(link h, link z, FILE *fp, int order);
static void tree_free(link h, link z);
static int height(link h, link z);
static void leaves(link h, link z, int *num);

static link NEW(Item item, link l, link r) {
  link x = malloc(sizeof *x);
  if (x == NULL)
    return NULL;
  x->item = item; x->l = l; x->r = r;
  return x;
}

BST BSTinit( ) {
  BST bst = malloc(sizeof *bst);
  if (bst == NULL)
    return NULL;
  bst->N = 0;
  bst->root = bst->z = (link) ITEMsetNull();
  return bst;
}

BST BSTload(FILE *fin, BST bst) {
  Item x;
  if (bst == NULL)
    bst = BSTinit();
    if (bst == NULL)
      return NULL;
  while (!ITEMcheckNull(x = ITEMscan(fin))){
    BSTinsert_leaf(bst, x);
  }
  ITEMfree(x);
  return bst;
}

static int count(link h, link z) {
 if (h == NULL)
   return 0;
 return count(h->l, z) + count(h->r, z) +1;
}

int BSTcount(BST bst) {
  return count(bst->root, bst->z);
}

int BSTempty(BST bst) {
  if ( BSTcount(bst) == 0)
    return 1;
  else
    return 0;
}

Item BSTsearch(BST bst, Item x) {
  return searchR(bst->root, x, bst->z);
}

static Item searchR(link h, Item x, link z) {
  Item result = ITEMsetNull();
  if (h == z)
    return ITEMsetNull();
  if (IDcompare(x, h->item)==0)
    return h->item;
  result = searchR(h->l, x, z);
  if (!ITEMcheckNull(result))
    return result;
  result = searchR(h->r, x, z);
  return result;
}

static link insertR(link h, Item x, link z) {
  if (h == z) {
    ITEMstore(stdout, x);
    return NEW(x, z, z);
  }
  if (ITEMcompare(x, h->item)==-1)
    h->l = insertR(h->l, x, z);
  else
    h->r = insertR(h->r, x, z);
  return h;
}

void BSTinsert_leaf(BST bst, Item x) {
  bst->root = insertR(bst->root, x, bst->z);
  bst->N++;
}

static link rotR(link h) {
  link x = h->l;
  h->l = x->r;
  x->r = h;
  return x;
}

static link rotL(link h) {
  link x = h->r;
  h->r = x->l;
  x->l = h;
  return x;
}

static link insertT(link h, Item x, link z) {
  if ( h == z)
    return NEW(x, z, z);
  if (ITEMcompare(x, h->item)==-1) {
    h->l = insertT(h->l, x, z);
    h = rotR(h);
  }
  else {
    h->r = insertT(h->r, x, z);
    h = rotL(h);
  }
  return h;
}

void BSTinsert_root(BST bst, Item x) {
  bst->root = insertT(bst->root, x, bst->z);
  bst->N++;
}

static Item minR(link h, link z) {
  if (h == z)
    return ITEMsetNull();
  if (h->l == z)
    return (h->item);
  return minR(h->l, z);
}

Item BSTmin(BST bst) {
  return minR(bst->root, bst->z);
}

static Item maxR(link h, link z) {
  if (h == z)
    return ITEMsetNull();
  if (h->r == z)
    return (h->item);
  return maxR(h->r, z);
}

Item BSTmax(BST bst) {
  return maxR(bst->root, bst->z);
}

void BSTsort(BST bst, FILE *fout, int order) {
  if (bst == NULL) return;
  if (BSTempty(bst))
    return;
  tree_print(bst->root, bst->z, fout, order);
}

static void tree_print(link h, link z, FILE *fout, int order) {
  if (h == z)
    return;

  if (order == PREORDER)
    ITEMstore(fout, h->item);
  tree_print(h->l, z, fout, order);
  if (order == INORDER)
    ITEMstore(fout, h->item);
  tree_print(h->r, z, fout, order);
  if (order == POSTORDER)
    ITEMstore(fout, h->item);
}

static void tree_free(link h, link z) {
  if (h == z)
    return;
  tree_free(h->l, z);
  tree_free(h->r, z);
  ITEMfree(h->item);
  free(h);
}

void BSTfree(BST bst) {
  if (bst == NULL)
    return;
  tree_free(bst->root, bst->z);
  free(bst);
}

int BSTheight(BST bst) {
  return height(bst->root, bst->z);
}

static int height(link h, link z) {
  int u, v;
  if (h == z)
    return -1;
  u = height(h->l, z);
  v = height(h->r, z);
  if (u>v)
    return u+1;
  else
    return v+1;
}

int BSTleaves(BST bst){
  int num = 0;
  leaves(bst->root, bst->z, &num);
  return num;
}

static void leaves(link h, link z, int *num) {
  if ((h->l == z) && (h->r == z)) {
   (*num)++;
   return;
  }
  if (h->l != z)
    leaves(h->l, z, num);
  if (h->r != z)
    leaves(h->r, z,  num);
}




