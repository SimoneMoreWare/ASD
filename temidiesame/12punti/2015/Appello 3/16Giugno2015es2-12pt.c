#include <stdio.h>
#include <stdlib.h>

struct node {
    int key;
    struct node *left;
    struct node *right;
};

//Le funzioni utili ai fini dell'esercizio sono duplicateLeftChild e createNode. 
//Le altre sono per inizializzazione e stampa.

struct node *initializeTree();
struct node *createNode(int key, struct node *left, struct node *right);
void duplicateLeftChild(struct node *root);
void printTree(struct node *root);

int main()
{
    struct node* root;

    root = initializeTree();

    printf("Tree before duplicateLeftChild: \n\t");
    printTree(root);
    duplicateLeftChild(root);
    printf("\nTree after duplicateLeftChild: \n\t");
    printTree(root);

    return 0;
}

struct node *createNode(int key, struct node *left, struct node *right){
    struct node *newNode;

    newNode = malloc(sizeof(*newNode));

    newNode->key = key;
    newNode->left = left;
    newNode->right = right;

    return newNode;
};

struct node *initializeTree(){
    struct node *node1;
    struct node *node2;
    struct node *node3;

    node1 = createNode(1, NULL, NULL);
    node3 = createNode(3, NULL, NULL);
    node2 = createNode(2, node1, node3);

    return node2;
};

void duplicateLeftChild(struct node *root){
    if(root == NULL){
        return;
    }
    duplicateLeftChild(root->left);
    duplicateLeftChild(root->right);
    root->left = createNode(root->key, root->left, NULL);
    return;
}

void printTree(struct node *root){
    if(root == NULL){
        return;
    }

    printf("%d ", root->key);
    printTree(root->left);
    printTree(root->right);

    return;
}
