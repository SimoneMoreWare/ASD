#include <stdlib.h>
#include "Item.h"
#include "BST.h"


typedef struct BSTnode* link;
struct BSTnode { Item item; link l; link  r; } ;

struct binarysearchtree { link root; link z; };

static link NEW(Item item, link l, link r);
static void tree_free(link h, link z);
void sortPreorderR(FILE *fin, link h, link z);
static link readNodeR(FILE *fin, BST bst);
int countCompleteR(link h, link z, int l1, int l2, int depth);
int distCountR(link h, link z, Key k, int *miss);
int distanceR(link h, link z, Key k1, Key k2, int *miss);
link mirrorR(link h, link z);

static link NEW(Item item, link l, link r) {
  link x = malloc(sizeof *x);
  if (x == NULL) return NULL;
  x->item = item; x->l = l; x->r = r;
  return x;
}

BST BSTinit( ) {
  BST bst = malloc(sizeof *bst);
  if (bst == NULL) return NULL;
  bst->root = bst->z = (link) ITEMsetNull();
  return bst;
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

void sortPreorderR(FILE *fin, link h, link z) {
  if (h == z)
    return;
  ITEMstore(fin, h->item);
  sortPreorderR(fin, h->l, z);
  sortPreorderR(fin, h->r, z);
}

void BSTwritePreorder(FILE *fin, BST bst){
  sortPreorderR(fin, bst->root, bst->z);
}

static link readNodeR(FILE *fin, BST bst) {
  int l, r;
  link node, lp, rp;
  Item val;

  val = ITEMscan(fin);
  if (ITEMcheckNull(val))
    return NULL;

  if (fscanf(fin, "%d %d", &l, &r) != 2)
    return NULL;

  if (l!=0)
    lp = readNodeR(fin, bst);
  else
    lp = bst->z;
  if (r!=0)
    rp = readNodeR(fin, bst);
  else
    rp = bst->z;

  node = NEW(val, lp, rp);
  if (node == NULL) return NULL;
  return node;
}

BST BSTloadPreorder(FILE *fin) {
  BST bst = BSTinit();
  if (bst == NULL)
    return NULL;
  bst->root = readNodeR(fin, bst);
  if (bst->root == NULL) return NULL;
  return bst;
}

int countCompleteR(link h, link z, int l1, int l2, int depth) {
  int cnt = 0;
  if (h == z)
    return 0;
  if (depth > l2)
    return 0;
  if (depth >= l1)
    if (h->l != z && h->r != z)
      cnt = 1;
  return cnt + countCompleteR(h->l, z, l1, l2, depth+1) + countCompleteR(h->r, z, l1, l2, depth+1);
}

int BSTcountInRange(BST bst, int l1, int l2) {
  return countCompleteR(bst->root, bst->z, l1, l2, 0);
}

int distCountR(link h, link z, Key k, int *miss) {
  int ck;
  if (h == z) {
    *miss = 1;
	return 0;
  }
  ck = KEYcompare(KEYget(h->item), k);
  if (ck == 0)
    return 1;
  if (ck < 0)
    return 1+distCountR(h->r, z, k, miss);
  if (ck > 0)
    return 1+distCountR(h->l, z, k, miss);
  return 0;
}

int distanceR(link h, link z, Key k1, Key k2, int *miss) {
  int ck1, ck2;

  if(h == z) {
    *miss = 1;
    return 0;
  }
  ck1 = KEYcompare(KEYget(h->item), k1);
  ck2 = KEYcompare(KEYget(h->item), k2);

  if(ck1 < 0 && ck2 < 0)
    return distanceR(h->r, z, k1, k2, miss);
  if(ck2 > 0 && ck2 > 0)
    return distanceR(h->l, z, k1, k2, miss);
  if(ck1 == 0)
    return distCountR(h->r, z, k2, miss);
  if(ck2 == 0)
    return distCountR(h->l, z, k1, miss);
  return distCountR(h->r, z, k2, miss) + distCountR(h->l, z, k1, miss);
}

int BSTdistance(BST bst, Key k1, Key k2) {
  /* Assume k1 <= k2 */
  int miss = 0;
  int dist = distanceR(bst->root, bst->z, k1, k2, &miss);
  return (miss == 0) ? dist : -1;
}

link mirrorR(link h, link z) {
  link tmp;
  if(h == z)
    return z;
  tmp = h->l;
  h->l = mirrorR(h->r, z);
  h->r = mirrorR(tmp, z);
  return h;
}

void BSTmirror(BST bst) {
  bst->root = mirrorR(bst->root, bst->z);
}
