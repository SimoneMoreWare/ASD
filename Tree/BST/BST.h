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
Item BSTsearch(BST bst, Key k);
void BSTinsert_leafI(BST bst, Item x);
void BSTinsert_leafR(BST bst, Item x);
void BSTinsert_root(BST bst, Item x);
Item BSTmin(BST bst);
Item BSTmax(BST bst);
Item BSTsucc(BST bst, Key k);
Item BSTpred(BST bst, Key k);
Item BSTselect(BST bst, int r);
void BSTvisit(BST bst, int way);
void BSTdelete(BST bst, Key k);
void BSTbalance(BST bst);


#endif



