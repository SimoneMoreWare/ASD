#ifndef _BSTINCLUDED
#define _BSTINCLUDED
#include "skier.h"

typedef struct binarysearchtree* BST;

BST   BSTinit(void);
void  BSTfree(BST t);
int   BSTcount(BST t);
int   BSTempty(BST t);
skier BSTsearch(BST t, int id);
void  BSTinsert(BST t, skier d);

#endif

