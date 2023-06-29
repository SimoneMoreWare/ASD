#include "accessori.h"
#include <string.h>

typedef struct node *link;

struct node{
    Accessorio a;
    link right, left;
    int N;
};

struct accs{
   link root, z;
   int size;
};



static link NEWNode(Accessorio a, link left, link right, int N){
    link x=malloc(sizeof(*x));
    if(x==NULL) exit(EXIT_FAILURE);
    x->a=a;
    x->right=right;
    x->left=left;
    x->N=N;
    return x;
}

static Accessori BSTinit(){
    Accessori a;
    a=(Accessori)malloc(sizeof(struct accs));
    if(a==NULL) exit(EXIT_FAILURE);
    a->size=0;
    a->z=NEWNode(ACCESSORIOsetNull(), NULL, NULL, 0);
    a->root=a->z;
    return a;
}


static void freeTree(link head, link z){
    if(head==z)
        return;
    freeTree(head->left, z);
    freeTree(head->right, z);
    free(head);
    return;
}

static void BSTfree(Accessori a){
    if(a!=NULL){
       freeTree(a->root, a->z);
       free(a->z);
       free(a);
    }
    return;
}


static Accessorio searchR(link head, link z, char *nome){
    if(head==z){
        printf("L'accessorio %s non esiste.\n", nome);
        return ACCESSORIOsetNull();
    }
    if(strcmp(nome, head->a.nome)==0)
        return head->a;
    if(strcmp(nome, head->a.nome)<0)
        return searchR(head->left, z, nome);
    return searchR(head->right, z, nome);
}

static Accessorio BSTsearch(Accessori a, char *nome){
    return searchR(a->root, a->z, nome);
}


static link insertR(link head, link z, Accessorio acc){
    if(head==z)
        return NEWNode(acc, z, z, 1);
    if(strcmp(acc.nome, head->a.nome)<0){
        head->left=insertR(head->left, z, acc);
    }
    else if(strcmp(acc.nome, head->a.nome)>0){
        head->right=insertR(head->right, z, acc);
    }
    (head->N)++;
    return head;
}

static void BSTinsertLeaf(Accessori a, Accessorio acc){
    a->root=insertR(a->root, a->z, acc);
    return;
}


static link rotRightR(link head){
    link x;
    x=head->left;
    head->left=x->right;
    x->right=head;
    x->N=head->N;
    head->N=1;
    head->N+=(head->left)?head->left->N:0;
    head->N+=(head->right)?head->right->N:0;
    return x;
}

static link rotLeftR(link head){
    link x;
    x=head->right;
    head->right=x->left;
    x->left=head;
    x->N=head->N;
    head->N=1;
    head->N+=(head->left)?head->left->N:0;
    head->N+=(head->right)?head->right->N:0;
    return x;
}

static link partR(link head, int r){
    int t;
    t=head->left->N;
    if(t>r){
        head->left= partR(head->left, r);
        head=rotRightR(head);
    }
    if(t<r){
        head->right=partR(head->right, r-t-1);
        head=rotLeftR(head);
    }
    return head;
}

static link joinLR(link a, link b, link z){
    if(b==z)
        return a;
    b=partR(b, 0);
    b->left=a;
    b->N=a->N+b->right->N+1;
    return b;
}

static link deleteR(link head, link z, char *nome, Boolean *trovato){
    link y;
    if(head==z){
        printf("\nImpossibile eliminare l'accessorio %s: non esiste.\n", nome);
        return z;
    }
    if(strcmp(nome, head->a.nome)<0){
        head->left=deleteR(head->left, z, nome, trovato);
    }
    if(strcmp(nome, head->a.nome)>0){
        head->right=deleteR(head->right, z, nome, trovato);
    }
    (head->N)--;
    if(strcmp(nome, head->a.nome)==0){
        *trovato=VERO;
        y=head;
        head=joinLR(head->left, head->right, z);
        free(y);
    }
    return head;
}

static void BSTdelete(Accessori a, char *nome){
    Boolean trovato=FALSO;
    a->root=deleteR(a->root, a->z, nome, &trovato);
    if(trovato==VERO){
        printf("\nL'accessorio %s e' stato eliminato con successo.\n", nome);
        (a->size)--;
    }
    return;
}


Accessori ACCESSORIinit(){
    return BSTinit();
}


Accessori ACCESSORIread(FILE *f){
    Accessori a=ACCESSORIinit();
    Accessorio ac;
    ac=ACCESSORIOread(f);
    while(ACCESSORIOisNull(ac)==FALSO){
       BSTinsertLeaf(a, ac);
       a->size++;
       ac=ACCESSORIOread(f);
    }
    return a;
}


static void printR(link head, link z, FILE *f){
    if(head==z)
       return;
    printR(head->left, z, f);
    ACCESSORIOprint(head->a, f);
    printR(head->right, z, f);
    return;
}

void ACCESSORIprint(Accessori a, FILE *f){
    printR(a->root, a->z, f);
    return;
}


Accessorio ACCESSORIcercaAccessorio(Accessori a, char *nome){
    return BSTsearch(a, nome);
}


void ACCESSORIcancellaAccessorio(Accessori a, char *nomeAccessorio){
     BSTdelete(a, nomeAccessorio);
     return;
}


int ACCESSORIsize(Accessori a){
    return a->size;
}


void ACCESSORIfree(Accessori a){
   BSTfree(a);
   return;
}
