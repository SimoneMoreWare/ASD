#include <stdio.h>
#include <stdlib.h>

typedef struct node *link;

struct node {
    int item;
    link left;
    link right;
};

link NEW(int chiave, link left, link right);
link buildTree(int *inorder, int *preorder, int N);
link buildTreeR(int *inorder, int *preorder, int *i, int l, int r);
void printTreeInOrder(link root);

/*Struttura albero considerato

              (1)
              / \
            (2) (5)
            / \   \
          (3) (4) (6)
*/

int main()
{
    link root;

    int *preorder,*inorder, N = 6;

    preorder = malloc(N*sizeof(int));
    inorder = malloc(N*sizeof(int));

    preorder[0] = 1;
    preorder[1] = 2;
    preorder[2] = 3;
    preorder[3] = 4;
    preorder[4] = 5;
    preorder[5] = 6;

    inorder[0] = 3;
    inorder[1] = 2;
    inorder[2] = 4;
    inorder[3] = 1;
    inorder[4] = 5;
    inorder[5] = 6;

    root = buildTree(inorder,preorder,N-1);

    printTreeInOrder(root);

    return 0;
}

link NEW(int chiave, link left, link right){
    link x = malloc(sizeof *x);

    x->item = chiave;
    x->left = left;
    x->right = right;

    return x;
}

link buildTreeR(int *inorder, int *preorder, int *i, int l, int r){
    link root;
    int trovato = 1, j;

    if(l>r){
        return NULL;
    }

    if(l==r){
        root = NEW(preorder[*i],NULL,NULL);
        (*i)++;
        return root;
    }

    for(j=l; j<r && trovato; j++){
        if(preorder[*i] == inorder[j]){
            trovato = 0;
            root = NEW(preorder[*i],NULL,NULL);
            (*i)++;
            root->left = buildTreeR(inorder,preorder,i,l,j-1);
            root->right = buildTreeR(inorder,preorder,i,j+1,r);
        }
    }
    return root;
}

link buildTree(int *inorder, int *preorder, int N){
    int i=0;
    link root;

    root = buildTreeR(inorder,preorder,&i,0,N);

    return root;
}

void printTreeInOrder(link root){
    if(root == NULL)
        return;

    printf("%d ", root->item);
    printTreeInOrder(root->left);
    printTreeInOrder(root->right);

    return;
}
