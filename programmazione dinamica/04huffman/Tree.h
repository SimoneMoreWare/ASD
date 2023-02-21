#ifndef BST_H
#define BST_H

typedef struct  binarytree *Tree;

Tree    TREErootCreate(Item val);
Tree    TREEjoin(Tree tL, Tree tR);
Item    TREEgetRootItem(Tree t);
void    TREEdisplayCode(Tree t);
void    TREEvisit(Tree t);
int     TREEheight(Tree t);
void    TREEfree(Tree t);
#endif

