#ifndef _BSTINCLUDED
#define _BSTINCLUDED

typedef struct  binarysearchtree *BST;

BST  BSTinit(void);
void BSTfree(BST bst);
int  BSTempty(BST bst);
int  BSTsearch(BST bst, char *key);
void BSTinsert(BST bst, char *str, int i);

#endif

