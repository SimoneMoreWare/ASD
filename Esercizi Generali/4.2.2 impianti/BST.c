#include <stdio.h>
#include <stdlib.h>
#include "BST.h"

typedef struct BSTnode* link;
struct BSTnode { skier val; link l; link  r;} ;
struct binarysearchtree { link root; int num_nod; link z; };

static link NEW(skier d, link l, link r);
static void tree_free(link root);
static skier searchR(link root, int id, link z);
static link insertR(link h, skier d, link z);

static link NEW(skier d, link l, link r) {
  link x = malloc(sizeof *x);
  if (x == NULL) {
    printf("Errore di allocazione di memoria\n");
    exit(1);
  }
  x->val = d; x->l = l; x->r = r;
  return x;
}


BST BSTinit(void) {
  BST bst = malloc(sizeof *bst) ;
  if (bst == NULL) {
    printf("Errore di allocazione di memoria\n");
    exit(1);
  }
  bst->root =  NULL;
  bst->z = NULL;
  bst->num_nod = 0;
  return bst;
}

void BSTfree(BST bst) {
  if (bst == NULL)
    return;
  tree_free(bst->root);
  free(bst);
}

static void tree_free(link root) {
  if (root == NULL)
    return;
  tree_free(root->l);
  tree_free(root->r);
  SKIERfree(root->val);
  free(root);
}

int BSTempty(BST bst) {
 return (bst->num_nod==0);
}

int BSTcount(BST bst) {
  if (BSTempty(bst))
    return 0;
  return bst->num_nod;
}

static skier searchR(link root, int id, link z) {
  if (root == NULL)
    return NULL;
  if (SKIERid(root->val) == id)
    return root->val;
  if (SKIERid(root->val) > id)
    return searchR(root->l, id, z);
  else
    return searchR(root->r, id, z);
  }

skier BSTsearch(BST bst, int id) {
  return searchR(bst->root, id, bst->z);
}

static link insertR(link root, skier d, link z) {
  if (root == NULL)
    return NEW(d, z, z);

  if (SKIERid(root->val) == SKIERid(d))
    return root;

  if (SKIERid(root->val) > SKIERid(d))
    root->l = insertR(root->l, d, z);
  else
    root->r = insertR(root->r, d, z);
  return root;
}

void BSTinsert(BST bst, skier d) {
  bst->root = insertR(bst->root, d, bst->z);
  bst->num_nod++;
}

