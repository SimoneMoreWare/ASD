#include "Pacchi.h"
#include <string.h>

typedef struct node *link;

struct node{
    Pacco val;
    link right, left;
};

struct pacchi_s{
    link radice, z;
    int size;
};



//---STATIC---
static link NEWnode(Pacco p, link right, link left){
    link x=malloc(sizeof(*x));
    if(x==NULL){
        printf("Errore nell'allocazione.");
        exit(EXIT_FAILURE);
    }
    x->val=p;
    x->right=right;
    x->left=left;
    return x;
}


static link BSTinsertR(link head, link z, Pacco p){
    if(head==z)
        return NEWnode(p, z, z);
    if(strcmp(PACCOgetCode(&p), PACCOgetCode(&head->val))<0){
        head->left=BSTinsertR(head->left, z, p);
    }
    else{
        head->right=BSTinsertR(head->right, z, p);
    }
    return head;
}


static void BSTinsert(Pacchi p, Pacco po){
    p->radice=BSTinsertR(p->radice, p->z, po);
    return;
}


static Pacco* BSTsearchR(link head, link z, char *code){
    if(head==z){
        return NULL;
    }
    if(strcmp(code, PACCOgetCode(&head->val))==0)
        return &head->val;
    else if(strcmp(code, PACCOgetCode(&head->val))<0)
        return BSTsearchR(head->left, z, code);
    return BSTsearchR(head->right, z, code);
}


static void BSTfree(link head, link z){
    if(head==z)
        return;
    BSTfree(head->left, z);
    BSTfree(head->right, z);
    free(head);
    return;
}


static void BSTprintR(link head, link z, FILE *f){
    if(head==z)
        return;
    BSTprintR(head->left, z, f);
    PACCOprintCode(head->val, f);
    fprintf(f, "\n");
    BSTprintR(head->right, z, f);
    return;
}



//---PACCHI---
Pacchi PACCHIinit(){
    Pacchi p;
    p=(Pacchi)malloc(sizeof(struct pacchi_s));
    if(p==NULL){
        printf("Errore nell'allocazione.");
        exit(EXIT_FAILURE);
    }
    p->z=NEWnode(PACCOsetNull(), NULL, NULL);
    p->radice=p->z;
    p->size=0;
    return p;
}


Pacchi PACCHIread(FILE *f){
    Pacchi p=PACCHIinit();
    Pacco po;

    po=PACCOread(f);
    while(PACCOisNull(po)==FALSO){
        BSTinsert(p, po);
        po=PACCOread(f);
    }
    return p;
}


Pacco * PACCHIsearchPacco(Pacchi p, char *code){
    return BSTsearchR(p->radice, p->z, code);
}


void PACCHIprintCode(Pacchi p, FILE  *f){
    BSTprintR(p->radice, p->z, f);
    return;
}


void PACCHIfree(Pacchi p){
    if(p!=NULL){
        BSTfree(p->radice, p->z);
        free(p->z);
        free(p);
    }
}
