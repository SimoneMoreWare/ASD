#ifndef BSTDEF
#define BSTDEF

#include "skier.h"

typedef struct binarysearchtree *BST;

BST BSTinit() ;
void BSTfree(BST bst);
void BSTdestroy(BST bst);
int BSTcount(BST bst);
int BSTempty(BST bst);
skier BSTsearch(BST bst, int k);
void BSTinsert(BST bst, skier x);
void BSTprint(BST bst, FILE *fp);

#endif
