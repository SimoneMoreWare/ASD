#include <stdlib.h>
#include <stdio.h>
#include "Item.h"
#include "Tree.h"


typedef struct TREEnode* link;
struct TREEnode { Item item; link l; link  r; } ;

struct binarytree { link root; };

static int  heightR(link root);
static void displayR(link root, char *code, int pos);
static void visitR(link root);
static void freeR(link root);

link NEW(Item item, link l, link r) {
  link x = malloc(sizeof *x);
  x->item = item; x->l = l; x->r = r;
  return x;
}

Tree TREErootCreate(Item val) {
  Tree t = malloc(sizeof *t);
  t->root = NEW(val, NULL, NULL);
  return t;
}

Item TREEgetRootItem(Tree t) {
  return t->root->item;
}

int TREEheight(Tree t){
 return heightR(t->root);
}

int heightR(link root){
 int u, v;
 if (root == NULL)
   return -1;

 u = heightR(root->l);
 v = heightR(root->r);
 if (u>v)
   return u+1;
 else
   return v+1;
}


Tree TREEjoin(Tree tL, Tree tR) {
  Item val;
  Tree t = malloc(sizeof *t);
  val = ITEMmerge(TREEgetRootItem(tL), TREEgetRootItem(tR));
  t->root = NEW(val, tL->root, tR->root);
  return t;
}


void TREEdisplayCode(Tree t) {
  int h;
  char *code;
  h = TREEheight(t);
  code = calloc(h+1, sizeof(char));
  displayR(t->root, code, 0);
}

void displayR(link root, char *code, int pos) {
  if ((root->l==NULL) && (root->r == NULL)){
    code[pos] = '\0';
    printf("letter = %s code = %s\n", LETget(&root->item), code);
    return;
  }
  code[pos] = '0';
  displayR(root->l, code, pos+1);
  code[pos] = '1';
  displayR(root->r, code, pos+1);
}

void TREEvisit(Tree t) {
  visitR(t->root);
}

void visitR(link root) {
  if (root==NULL){
    return;
  }
  ITEMstore(root->item);
  visitR(root->l);
  visitR(root->r);
}

void TREEfree(Tree t) {
  freeR(t->root);
  free(t);
}

void freeR(link root) {
  if(root == NULL)
    return;
  freeR(root->l);
  freeR(root->r);
  free(root);
}
