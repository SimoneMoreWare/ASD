#include "produttori.h"
#include <string.h>

typedef struct NODE *LINK;

struct NODE{
   Produttore p;
   LINK right, left;
   int N;
};

struct prods_s{
   LINK root, z;
   int size;
};



static LINK NEWNode(Produttore p, LINK left, LINK right, int N){
    LINK x=malloc(sizeof(*x));
    if(x==NULL) exit(EXIT_FAILURE);
    x->p=p;
    x->right=right;
    x->left=left;
    x->N=N;
    return x;
}

static Produttori BSTinit(){
    Produttori p;
    p=(Produttori)malloc(sizeof(struct prods_s));
    if(p==NULL) exit(EXIT_FAILURE);
    p->size=0;
    p->z=NEWNode(PRODUTTOREsetNull(), NULL, NULL, 0);
    p->root=p->z;
    return p;
}


static Produttore searchR(LINK head, LINK z, char *nome){
    if(head==z)
        return PRODUTTOREsetNull();
    if(strcmp(nome, PRODUTTOREgetNome(head->p))==0)
        return head->p;
    if(strcmp(nome, PRODUTTOREgetNome(head->p))<0)
        return searchR(head->left, z, nome);
    return searchR(head->right, z, nome);
}

static Produttore BSTsearch(Produttori p, char *produttore){
    return searchR(p->root, p->z, produttore);
}


static LINK rotRightR(LINK head){
    LINK x;
    x=head->left;
    head->left=x->right;
    x->right=head;
    x->N=head->N;
    head->N=1;
    head->N+=(head->left)?head->left->N:0;
    head->N+=(head->right)?head->right->N:0;
    return x;
}

static LINK rotLeftR(LINK head){
    LINK x;
    x=head->right;
    head->right=x->left;
    x->left=head;
    x->N=head->N;
    head->N=1;
    head->N+=(head->left)?head->left->N:0;
    head->N+=(head->right)?head->right->N:0;
    return x;
}

static LINK partR(LINK head, int r){
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

static LINK joinLR(LINK a, LINK b, LINK z){
    if(b==z)
        return a;
    b=partR(b, 0);
    b->left=a;
    b->N=a->N+b->right->N+1;
    return b;
}

static LINK deleteR(LINK head, LINK z, char *nome, Boolean *trovato){
    LINK y;
    if(head==z){
        printf("\nImpossibile eliminare il produttore %s: non esiste.\n", nome);
        return z;
    }
    if(strcmp(nome, PRODUTTOREgetNome(head->p))<0){
        head->left=deleteR(head->left, z, nome, trovato);
    }
    if(strcmp(nome, PRODUTTOREgetNome(head->p))>0){
        head->right=deleteR(head->right, z, nome, trovato);
    }
    (head->N)--;
    if(strcmp(nome, PRODUTTOREgetNome(head->p))==0){
        *trovato=VERO;
        y=head;
        head=joinLR(head->left, head->right, z);
        free(y);
    }
    return head;
}

static void BSTdelete(Produttori p, char *nome){
    Boolean trovato=FALSO;
    p->root=deleteR(p->root, p->z, nome, &trovato);
    if(trovato==VERO){
        (p->size)--;
        printf("\nIl produttore %s e' stato eliminato con successo.\n", nome);
    }
    return;
}


static LINK insertR(LINK head, LINK z, Produttore p){
    if(head==z)
        return NEWNode(p, z, z, 1);
    if(strcmp(PRODUTTOREgetNome(p), PRODUTTOREgetNome(head->p))<0)
        head->left=insertR(head->left, z, p);
    else if (strcmp(PRODUTTOREgetNome(p), PRODUTTOREgetNome(head->p))>0)
        head->right=insertR(head->right, z, p);
    (head->N)++;
    return head;
}

static void BSTinsertInLeaf(Produttori p, Produttore pr){
    p->root=insertR(p->root, p->z, pr);
    return;
}


static void freeTree(LINK head, LINK z){
    if(head==z)
        return;
    freeTree(head->left, z);
    freeTree(head->right, z);
    PRODUTTOREfree(head->p);
    free(head);
    return;
}

static void BSTfree(Produttori p){
    if(p!=NULL){
        freeTree(p->root, p->z);
        free(p->z);
        free(p);
    }
    return;
}


Produttori PRODUTTORIinit(){
   return BSTinit();
}


Produttori PRODUTTORIread(FILE *f){
   Produttori p=PRODUTTORIinit();
   Produttore pr;
   pr=PRODUTTOREread(f);
   while(PRODUTTOREisNull(pr)==FALSO){
      BSTinsertInLeaf(p, pr);
      p->size++;
      pr=PRODUTTOREread(f);
   }
   return p;
}


static void printR(LINK head, LINK z, FILE *f){
   if(head==z)
      return;
   printR(head->left, z, f);
   PRODUTTOREprint(head->p, f);
   fprintf(f, "\n");
   printR(head->right, z, f);
   return;
}

void PRODUTTORIprint(Produttori p, FILE *f){
   printR(p->root, p->z, f);
   return;
}


Produttore PRODUTTORIcercaProduttore(Produttori p, char *produttore){
   return BSTsearch(p, produttore);
}


void PRODUTTORIeliminaProduttore(Produttori p, char *produttore){
   BSTdelete(p, produttore);
   return;
}


int PRODUTTORIsize(Produttori p){
   return p->size;
}


void PRODUTTORIcompattaProduttori(Produttori p, char *prod1, char *prod2){
    Produttore p1, p2;
    p1=PRODUTTORIcercaProduttore(p, prod1);
    p2=PRODUTTORIcercaProduttore(p, prod2);
    if(PRODUTTOREisNull(p1)==VERO && PRODUTTOREisNull(p2)==VERO){
        printf("\nI produttori %s e %s non esistono.\n", prod1, prod2);
       return;
    }
    if(PRODUTTOREisNull(p1)==VERO){
       printf("\nIl produttore %s non esiste.\n", prod1);
       return;
    }
    if(PRODUTTOREisNull(p2)==VERO){
       printf("\nIl produttore %s non esiste.\n", prod2);
       return;
    }
    PRODUTTOREaccorpaProduttori(p1, p2);
    printf("\nI modelli di %s sono stati attributi a %s con successo.", prod2, prod1);
    PRODUTTORIeliminaProduttore(p, prod2);
    return;
}


void PRODUTTORIfree(Produttori p){
   BSTfree(p);
   return;
}
