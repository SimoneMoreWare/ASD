#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAXS 11 /* 10 + 1 per '\0' */

typedef struct node *link;

struct node {
  char name[MAXS];
  link left;
  link right;
};

typedef char *Key;

int KEYcomp(Key a, Key b) {
  return strcmp(a, b);
}

link newNode(char *key);
link readNode_nodo(FILE *in);
link readTree(char *filename);
void freeTree(link root);
void preOrder(link root);
void inOrder(link root);
void postOrder(link root);
int count(link root);
int height(link root);

int main() {
  link root;
  root = readTree("tree.txt");

  printf("Number of nodes: %d\n", count(root));
  printf("Tree height: %d\n", height(root));
  printf("Preorder visit:\n");
  preOrder(root);
  printf("\nInorder visit:\n");
  inOrder(root);
  printf("\nPostorder visit:\n");
  postOrder(root);

  freeTree(root);
  return 0;
}

link newNode(char *key) {
  link n = malloc(1*sizeof(*n));
  strcpy (n->name,key);
  n->left = NULL;
  n->right = NULL;
  return n;
}

void preOrder(link root){
  if (root == NULL)
    return;
  printf("%s ",root->name);
  preOrder(root->left);
  preOrder(root->right);
}

void inOrder(link root){
  if (root == NULL)
    return;
  inOrder(root->left);
  printf("%s ",root->name);
  inOrder(root->right);
}

void postOrder(link root){
  if (root == NULL)
    return;
  postOrder(root->left);
  postOrder(root->right);
  printf("%s ",root->name);
}

int count(link root) {
 if (root == NULL)
   return 0;
 return count(root->left) + count(root->right) + 1;
}

int height(link root) {
 int u, v;
 if (root == NULL)
   return -1;
 u = height(root->left); v = height(root->right);
 if (u>v)
   return u+1;
 else
   return v+1;
}

void freeTree(link root) {
  if (root == NULL)
    return;
  freeTree(root->left);
  freeTree(root->right);
  free(root);
}

link readNode(FILE *in) {
  char key[MAXS];
  int l, r;
  link n;
  if (fscanf(in, "%s %d %d", key, &l, &r) != 3)
    return NULL;
  n = newNode(key);
  if (l!=0)
    n->left = readNode(in);
  if (r!=0)
    n->right = readNode(in);
  return n;
}

link readTree(char *filename) {
  FILE *in;
  link root;

  in = fopen(filename, "r");
  root = readNode(in);
  fclose(in);
  return root;
}

