#ifndef BST_H_DEFINED
#define BST_H_DEFINED

typedef struct  binarysearchtree *BST;

BST	    BSTinit(void) ;
void    BSTfree(BST t);
int     BSTcountInRange(BST t, int l1, int l2);
BST     BSTloadPreorder(FILE *fin);
int     BSTdistance(BST, Key k1, Key k2);
void    BSTmirror(BST t);
void    BSTwritePreorder(FILE *fin, BST t);

#endif
