#include "modelli.h"
#include<string.h>

typedef struct Node *Link;

struct Node{
    Modello m;
    Link right, left;
    int N;
};

struct mods_s{
    Link root, z;
    int size;
};



static Link NEWNode(Modello m, Link left, Link right, int N){
    Link x=malloc(sizeof(*x));
    if(x==NULL) exit(EXIT_FAILURE);
    x->m=m;
    x->right=right;
    x->left=left;
    x->N=N;
    return x;
}

static Modelli BSTinit(){
    Modelli m;
    m=(Modelli)malloc(sizeof(struct mods_s));
    if(m==NULL) exit(EXIT_FAILURE);
    m->size=0;
    m->z=NEWNode(MODELLOsetNull(), NULL, NULL, 0);
    m->root=m->z;
    return m;
}


static void freeTree(Link head, Link z){
    if(head==z)
        return;
    freeTree(head->left, z);
    freeTree(head->right, z);
    MODELLOfree(head->m);
    free(head);
    return;
}

static void BSTfree(Modelli m){
    if(m!=NULL){
        freeTree(m->root, m->z);
        free(m->z);
        free(m);
    }
    return;
}


static Modello searchR(Link head, Link z, char *nome){
    if(head==z)
        return MODELLOsetNull();
    if(strcmp(nome, MODELLOgetNome(head->m))==0)
        return head->m;
    if(strcmp(nome, MODELLOgetNome(head->m))<0)
        return searchR(head->left, z, nome);
    return searchR(head->right, z, nome);
}

static Modello BSTsearch(Modelli m, char *nome){
    return searchR(m->root, m->z, nome);
}


static Link insertR(Link head, Link z, Modello md){
    if(head==z)
        return NEWNode(md, z, z, 1);
    if(strcmp(MODELLOgetNome(md), MODELLOgetNome(head->m))<0){
        head->left=insertR(head->left, z, md);
    }
    else if(strcmp(MODELLOgetNome(md), MODELLOgetNome(head->m))>0){
        head->right=insertR(head->right, z, md);
    }
    (head->N)++;
    return head;
}

static void BSTinsertLeaf(Modelli m, Modello md){
    m->root=insertR(m->root, m->z, md);
    return;
}


static Link rotRightR(Link head){
    Link x;
    x=head->left;
    head->left=x->right;
    x->right=head;
    x->N=head->N;
    head->N=1;
    head->N+=(head->left)?head->left->N:0;
    head->N+=(head->right)?head->right->N:0;
    return x;
}

static Link rotLeftR(Link head){
    Link x;
    x=head->right;
    head->right=x->left;
    x->left=head;
    x->N=head->N;
    head->N=1;
    head->N+=(head->left)?head->left->N:0;
    head->N+=(head->right)?head->right->N:0;
    return x;
}

static Link partR(Link head, int r){
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

static Link joinLR(Link a, Link b, Link z){
    if(b==z)
        return a;
    b=partR(b, 0);
    b->left=a;
    b->N=a->N+b->right->N+1;
    return b;
}

static Link deleteR(Link head, Link z, char *nome, Boolean *trovato){
    Link y;
    if(head==z){
        printf("\nImpossibile eliminare il modello %s: non esiste.\n", nome);
        return z;
    }
    if(strcmp(nome, MODELLOgetNome(head->m))<0){
        head->left=deleteR(head->left, z, nome, trovato);
    }
    if(strcmp(nome, MODELLOgetNome(head->m))>0){
        head->right=deleteR(head->right, z, nome, trovato);
    }
    (head->N)--;
    if(strcmp(nome, MODELLOgetNome(head->m))==0){
        *trovato=VERO;
        y=head;
        head=joinLR(head->left, head->right, z);
        free(y);
    }
    return head;
}

static void BSTdelete(Modelli m, char *nome){
    Boolean trovato=FALSO;
    m->root=deleteR(m->root, m->z, nome, &trovato);
    if(trovato==VERO){
        printf("\nIl modello %s e' stato eliminato con successo.\n", nome);
        (m->size)--;
    }
    return;
}


Modelli MODELLIinit(){
   return BSTinit();
}


Modelli MODELLIread(FILE *f){
   Modelli m=MODELLIinit();
   Modello md;
   md=MODELLOread(f);
   while(MODELLOisNull(md)==FALSO){
      BSTinsertLeaf(m, md);
      m->size++;
      md=MODELLOread(f);
   }
   return m;
}


static void printR(Link head, Link z, FILE *f){
    if(head==z)
       return;
    printR(head->left, z, f);
    MODELLOprint(head->m, f);
    fprintf(f, "\n");
    printR(head->right, z, f);
    return;
}

void MODELLIprint(Modelli m, FILE *f){
    printR(m->root, m->z, f);
    return;
}


void MODELLIcancellaModello(Modelli m, char *modello){
    BSTdelete(m, modello);
    return;
}


Modello MODELLIcercaModello(Modelli m, char *modello){
   return BSTsearch(m, modello);
}


int MODELLIsize(Modelli m){
    return m->size;
}


void spostaR(Modelli m1, Link head, Link z){
    if(head==z)
        return;
    spostaR(m1, head->left, z);
    BSTinsertLeaf(m1, head->m);
    spostaR(m1, head->right, z);
    return;
}

void MODELLIspostaModelli(Modelli m1, Modelli m2){
    spostaR(m1, m2->root, m2->z);
    return;
}


void MODELLIfree(Modelli m){
    BSTfree(m);
    return;
}
