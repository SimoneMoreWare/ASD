#include<stdlib.h>
#include<string.h>
#include<stdio.h>

typedef int KEY;

typedef struct node_ {
  KEY k;
  struct node_ *l, *r;
} node;

typedef node* link;

int KEYcmp(KEY k1, KEY k2) {
  return (k1 == k2);
}

link newNode(KEY k, link l, link r) {
  link n = calloc(1, sizeof(node));
  n->k = k;
  n->l = l;
  n->r = r;
  return n;
}

int subtreeR(link root1, link root2) {
    if (root1 == NULL && root2 == NULL)
        return 1;

    if (root1 == NULL || root2 == NULL)
        return 0;

    return (KEYcmp(root1->k, root2->k) && subtreeR(root1->l, root2->l) && subtreeR(root1->r, root2->r));
}

int subtree(link root1, link root2) {
    if (root1 == NULL)
        return 0;

    if (root2 == NULL)
        return 1;

    if (subtreeR(root1, root2))
        return 1;

    return subtree(root1->l, root2) || subtree(root1->r, root2);
}

void freeTree(link root) {
  if (root == NULL)
    return;
  freeTree(root->l);
  freeTree(root->r);
  free(root);
}

int main() {

  link t = newNode(10, newNode(5, newNode(3, newNode(2, NULL, NULL), NULL), NULL), newNode(6, NULL, NULL));
  link s1 = newNode(5, newNode(3, newNode(2, NULL, NULL), NULL), NULL);
  link s2 = newNode(3, newNode(3, NULL, NULL), NULL);
  link s3 = newNode(3, newNode(2, NULL, NULL), NULL);
  printf("Primo sottoalbero = %d\n", subtree(t, s1));
  printf("Secondo sottoalbero = %d\n", subtree(t, s2));
  printf("Terzo sottoalbero = %d\n", subtree(t, s3));
  freeTree(t);
  freeTree(s1);
  freeTree(s2);
  freeTree(s3);
  return 0;
}
