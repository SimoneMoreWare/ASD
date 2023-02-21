#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED


typedef struct bst* link, bst;
typedef struct bst_t* BST, bst_t;
typedef char* KEY;

//-----------------------------------

void bstreadPreorder(FILE* fl, BST a);
void bstinsert_leafI(link a, KEY x);
int subtree(link root1, link root2);
void subtree2(link root1, link root2, int* a);
BST BSTinit();
link getroot(BST a);
int keycmp(KEY s1, KEY s2);


#endif // BST_H_INCLUDED
