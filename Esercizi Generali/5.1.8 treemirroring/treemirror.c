#include<stdlib.h>
#include<string.h>
#include<stdio.h>

typedef struct node* link;
struct node { int k; link l; link  r; } ;

link newNode(int key, link l, link r) {
  link x = malloc(sizeof *x);
  if (x == NULL) return NULL;
  x->k = key; x->l = l; x->r = r;
  return x;
}

static void tree_free(link h, link z) {
  if (h == z)
    return;
  tree_free(h->l, z);
  tree_free(h->r, z);
  free(h);
}

void freeTree(link root) {
  link z = NULL;
  if (root == NULL)
    return;
  tree_free(root, z);
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

link mirror(link root) {
  link to=newNode(0, NULL, NULL), z = NULL;
  to = mirrorR(root, z);
  return to;
}


void treePrint (link root) {
  if (root == NULL){
    return;
  }
  printf ("%2d ", root->k);
  treePrint (root->l);
  treePrint (root->r);

  return;
}


int main() {

/*  link from = newNode(3,newNode(7,newNode(2, NULL, NULL), newNode(2, newNode(9, NULL, NULL), NULL)), newNode(1, NULL, newNode(0, NULL, NULL))); */
  link from = newNode(15, newNode(6, newNode(3, newNode(2, NULL, NULL), newNode(4, NULL, NULL)), newNode(7, NULL, NULL)), newNode(18, newNode(17, NULL, NULL), newNode(20, NULL, NULL)));
  link to;

  fprintf (stdout, "Original Tree (preorder): \n");
  treePrint (from);
  fprintf (stdout, "\n");

  fprintf (stdout, "Mirror Tree (preorder): \n");
  to = mirror(from);
  treePrint (to);
  fprintf (stdout, "\n");

  freeTree(to);
  return 0;
}
