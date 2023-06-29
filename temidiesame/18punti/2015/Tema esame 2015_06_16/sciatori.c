#include "sciatori.h"

typedef struct Node *Link;

struct Node{
   Sciatore s;
   Link right, left;
};

struct sc_s{
   Link radice, z;
};



static Link NEWnode(Sciatore val, Link right, Link left){
    Link x=malloc(sizeof(struct Node));
    if(x==NULL) exit(EXIT_FAILURE);
    x->s=val;
    x->right=right;
    x->left=left;
    return x;
}

static Sciatori BSTinit(){
    Sciatori s;
    s=(Sciatori)malloc(sizeof(struct sc_s));
    if(s==NULL) exit(EXIT_FAILURE);
    s->z=NEWnode(SCIATOREsetNull(), NULL, NULL);
    s->radice=s->z;
    return s;
}


static Sciatore *searchR(Link head, Link z, long id){
    if(head==z)
        return NULL;
    if(id < head->s.cardId)
        return searchR(head->left, z, id);
    else if (id > head->s.cardId)
        return searchR(head->right, z, id);
    return &head->s;
}

static Sciatore *BSTsearch(Sciatori s, long id){
    return searchR(s->radice, s->z, id);
}


static Link insertR(Link head, Link z, Sciatore s){
    if(head==z){
        return NEWnode(s, z, z);
    }
    if(s.cardId < head->s.cardId){
        head->left=insertR(head->left, z, s);
    }
    else if (s.cardId > head->s.cardId){
        head->right=insertR(head->right, z, s);
    }
    return head;
}

static void BSTinsertInLeaf(Sciatori s, Sciatore sc){
    s->radice=insertR(s->radice, s->z, sc);
    return;
}


static void treeFree(Link head, Link z){
    if(head==z)
        return;
    treeFree(head->left, z);
    treeFree(head->right, z);
    SCIATOREclear(head->s);
    free(head);
    return;
}

static void BSTfree(Sciatori s){
    if(s!=NULL){
        treeFree(s->radice, s->z);
        free(s->z);
        free(s);
    }
    return;
}


Sciatori SCIATORIinit(){
   return BSTinit();
}


Sciatore *SCIATORIsearch(Sciatori s, long id){
   return BSTsearch(s, id);
}


void SCIATORIadd(Sciatori s, Sciatore sc){
   BSTinsertInLeaf(s, sc);
   return;
}


static void printR(Link head, Link z, FILE *f){
    if(head==z)
        return;
    printR(head->left, z, f);
    SCIATOREprint(head->s, f);
    printR(head->right, z, f);
    return;
}

void SCIATORIprint(Sciatori s, FILE *f){
    printR(s->radice, s->z, f);
    return;
}


void SCIATORIfree(Sciatori s){
   BSTfree(s);
   return;
}
