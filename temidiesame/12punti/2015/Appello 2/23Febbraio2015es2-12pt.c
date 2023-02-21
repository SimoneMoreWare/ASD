#include <stdio.h>
#include <stdlib.h>

/* Albero considerato di altezza 4:

                   ( 1 )
                 /       \
               ( 2 )    ( 5 )
                /  \      /
             ( 3 )( 4 )( 6 )
                          \
                         ( 7 )
*/

struct node {
    int  key;
    struct node *left;
    struct node *right;
};

struct node *initializeTree(struct node *root);
void printPaths(struct node *root, int h, int pos, int *path);

int main()
{
    struct node *root = NULL;
    int *path,h=4,i;

    path = malloc(h*sizeof(int));

    //suppongo che tutte le chiavi dell'albero siano positive, quindi inizializzo path (il vettore delle soluzioni) a -1;
    for(i=0; i<h;i++)
        path[i] = -1;

    root = initializeTree(root);

    printPaths(root,h,0,path);

    return 0;
}

struct node *initializeTree(struct node *root){
    struct node *nodo1, *nodo2, *nodo3, *nodo4, *nodo5, *nodo6, *nodo7;

    nodo1 = malloc(sizeof(struct node));
    nodo2 = malloc(sizeof(struct node));
    nodo3 = malloc(sizeof(struct node));
    nodo4 = malloc(sizeof(struct node));
    nodo5 = malloc(sizeof(struct node));
    nodo6 = malloc(sizeof(struct node));
    nodo7 = malloc(sizeof(struct node));

    nodo1->key = 1;
    nodo2->key = 2;
    nodo3->key = 3;
    nodo4->key = 4;
    nodo5->key = 5;
    nodo6->key = 6;
    nodo7->key = 7;

    nodo1->left = nodo2;
    nodo1->right = nodo5;

    nodo2->left = nodo3;
    nodo2->right = nodo4;

    nodo3->left = NULL;
    nodo3->right = NULL;

    nodo4->left = NULL;
    nodo4->right = NULL;

    nodo5->left = nodo6;
    nodo5->right = NULL;

    nodo6->left = nodo7;
    nodo6->right = NULL;

    nodo7->left = NULL;
    nodo7->right = NULL;

    return nodo1;
}

void printPaths(struct node *root, int h, int pos, int *path){
    int i;

    if(root == NULL)
        return;

    if(root->left == NULL && root->right == NULL){
        path[pos] = root->key;

        for(i=0; i<h;i++)
            if(path[i]!=-1)
                printf("%d ", path[i]);
        printf("\n");
        return;
    }

    path[pos] = root->key;
    printPaths(root->left, h, pos+1,path);
    printPaths(root->right, h, pos+1,path);
    return;
}
