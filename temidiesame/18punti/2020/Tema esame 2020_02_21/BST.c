#include "BST.h"

typedef struct node *link;

struct node{
    Menu val;
    link right, left;
};

struct tree{
    link radice;
    link z;
};



static link newNode(Menu val, link left, link right){
    link x=malloc(sizeof(struct node));
    x->val=val;
    x->left=left;
    x->right=right;
    return x;
}


BST BSTinit(){
    BST bst;
    bst=(BST)malloc(sizeof(struct tree));
    if(bst==NULL)
       exit(EXIT_FAILURE);
    bst->z=newNode(MENUsetNull(), NULL, NULL);
    bst->radice=bst->z;
    return bst;
}


static link BSTinsertR(link head, link z, Menu m){
    if(head==z)
       return newNode(m, z, z);
    if(MENUcompare(m, head->val)==PRIMA){
       head->left=BSTinsertR(head->left, z, m);
    }
    else if(MENUcompare(m, head->val)==DOPO){
       head->right=BSTinsertR(head->right, z, m);
    }
    return head;
}


void BSTinsertLeaf(BST bst, Menu m){
    bst->radice=BSTinsertR(bst->radice, bst->z, m);
    return;
}


void treeFreeR(link head, link z){
    if(head==z)
       return;
    treeFreeR(head->left, z);
    MENUclear(head->val);
    treeFreeR(head->right, z);
    free(head);
    return;
}


void BSTfree(BST bst){
    if(bst!=NULL){
       treeFreeR(bst->radice, bst->z);
       free(bst->z);
       free(bst);
    }
    return;
}


static void BSTprintR(link head, link z, Piatti p, FILE *f){
    if(head==z)
       return;
    BSTprintR(head->left, z, p, f);
    MENUprint(head->val, p, f);
    fprintf(f, "\n");
    BSTprintR(head->right, z, p, f);
    return;
}


void BSTprint(BST bst, Piatti p, FILE *f){
    BSTprintR(bst->radice, bst->z, p, f);
    return;
}
