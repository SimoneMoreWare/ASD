#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED
#include "menu.h"

typedef struct tree *BST;

BST BSTinit();
void BSTfree(BST bst);
void BSTinsertLeaf(BST bst, Menu m);
void BSTprint(BST bst, Piatti p, FILE *f);

#endif // BST_H_INCLUDED
