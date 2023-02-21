#ifndef BST_H
#define BST_H

#define PREORDER  -1
#define INORDER    0
#define POSTORDER  1

typedef struct  binarysearchtree *BST;

BST  BSTinit(void);
void BSTfree(BST bst);
int  BSTcount(BST bst);
int  BSTempty(BST bst);
Item BSTsearch(BST bst, Item x);
void BSTinsert_leaf(BST bst, Item x);
void BSTinsert_root(BST bst, Item x);
Item BSTmin(BST bst);
Item BSTmax(BST bst);
BST  BSTload(FILE *fin, BST bst);
void BSTsort(BST bst, FILE *fin, int way);
int  BSTheight(BST bst);
int  BSTleaves(BST bst);

#endif

