#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bst.h"


struct bst
{
    KEY key;
    link right;
    link left;
};

struct bst_t
{
    link root;
    link z;
};
//-----------------------------------------


link bstinit()
{
    char name[10]="";

    link a=malloc(sizeof(bst));
    a->right=NULL;
    a->left=NULL;
    a->key=strdup(name);

    return a;
}

BST BSTinit()
{
    BST a=malloc(sizeof(bst_t));
    a->root=bstinit();
    a->z=NULL;
    return a;
}

int subtree(link root1, link root2)
{
    int a=0;

    subtree2(root1, root2, &a);
    if(a==0) a=1;
    //la funzione ritorna 1 se  il secondo albero non è incluso nel primo

    return a;
}

void subtree2(link root1, link root2, int* a)
{
    static int fl=0;
    char name[10];

    if(*a!=0)
        return;

    if(keycmp(root1->key, root2->key)!=0 && fl==0)
    {
        if(root1->left!=NULL)
            subtree2(root1->left, root2, a);
        if(root1->right != NULL)
            subtree2(root1->right, root2, a);

        return;
    }
    else
    {

        if(keycmp(root1->key, root2->key)!=0)
        *a=1;

    if(root1->left == NULL && root2->left!= NULL)
        {
            *a=1;
            return;
        }

    if(root1->right == NULL && root2->right != NULL)
        {
            *a=1;
            return;
        }


    if(root1->left!=NULL && root2->left!=NULL)
            subtree2(root1->left, root2->left, a);
        if(root1->right != NULL && root2->right != NULL)
            subtree2(root1->right, root2->right , a);
        if(*a==0)
           *a=2;

    }

    return;
}

int keycmp(KEY s1, KEY s2) // funzione inutile si poteva utilizzare
{                         // direttamente la strcmp, creata in quanto utilizzata
    return strcmp(s1, s2); // nel compito cartaceo
}

//--------------------------------------------

link getroot(BST a)
{
    return a->root;
}


int keyscan(FILE* fl1, KEY key)
{

    if(fscanf(fl1 ,"%s",key)!=EOF)
    return 0;

    return -1;
}


void bstreadPreorder(FILE* fl1, BST a)
{

    char name[10];
    int f=0;


    if(keyscan(fl1 ,name)!=-1)
        strcpy(a->root->key, name);
        else exit(-3);


    do{

        if(keyscan(fl1 ,name)!=-1)
        bstinsert_leafI(a->root, name);
        else
            f=-1;

    }while(f!=-1);

        fclose(fl1);


    return ;
}

void bstinsert_leafI(link a, KEY x)
{
    link p = a, h = p;


    while (h != NULL)
     {
        p = h;
         if(strcmp(x, h->key)<0)
            h=h->left;
                else h=h->right;
     }
    h = bstinit();
    strcpy(h->key, x);
    if (strcmp(x, p->key)<0)
       p->left = h;
    else
        p->right = h;
    return;
}

//--------------------------------------------
