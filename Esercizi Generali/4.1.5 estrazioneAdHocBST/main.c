#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Item.h"
#include "BST.h"

int main(int argc, char **argv) {
  FILE *in, *out;
  BST tree = NULL;
  int l1, l2, d;
  Key k1, k2;
  if (argc < 3)
    exit(-1);
  in = fopen(argv[1], "r");
  if (in==NULL) {
    printf("Error opening file %s\n", argv[1]);
    exit(1);
  }
  tree = BSTloadPreorder(in);
  if (tree == NULL) exit(-1);
  fclose(in);

  printf("Preorder visit of BST loaded from file:\n");
  BSTwritePreorder(stdout,tree);

  printf("Input 2 levels: ");
  scanf("%d %d", &l1, &l2);
  printf("Number of complete nodes between %d and %d: %d\n", l1, l2, BSTcountInRange(tree,l1,l2));

  printf("Input keys for computing distance: ");
  k1 = KEYscan();
  if (k1 == NULL) exit(-1);
  k2 = KEYscan();
  if (k2 == NULL) exit(-1);

  d = BSTdistance(tree,k1,k2);
  if (d == -1)
    printf("Nodes %s and %s don't belong to the same tree\n", k1, k2);
  else
    printf("Distance from node with key %s to node with key %s: %d\n", k1, k2, d);
  KEYfree(k1);
  KEYfree(k2);
  BSTmirror(tree);

  out = fopen(argv[2], "w");
  if (out==NULL) {
    printf("Error opening file %s\n", argv[2]);
    return 1;
  }
  printf("Tree after mirroring stored on file\n");
  BSTwritePreorder(out,tree);

  BSTfree(tree);
  fclose(out);
  return 0;
}
