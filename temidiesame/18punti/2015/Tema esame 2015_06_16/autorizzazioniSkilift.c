#include "autorizzazioniSkilift.h"

//AUTORIZZAZIONE SKILIFT
AutorizzazioneSk AUTORIZZAZIONESKcrea(long sciatore){
    AutorizzazioneSk as;
    as.sciatore=sciatore;
    as.nVolte=0;
    return as;
}


AutorizzazioneSk AUTORIZZAZIONESKsetNull(){
    AutorizzazioneSk as;
    as.sciatore=-1;
    as.nVolte=-1;
    return as;
}


void AUTORIZZAZIONESKincrementaNumVolte(AutorizzazioneSk *as){
    (as->nVolte)++;
    return;
}


void AUTORIZZAZIONESKprint(AutorizzazioneSk as, FILE *f){
    fprintf(f, "\tSciatore: %ld - Numero Volte: %d\n", as.sciatore, as.nVolte);
    return;
}



//AUTORIZZAZIONI SCIATORE
typedef struct nodo *coll;

struct nodo{
    AutorizzazioneSk val;
    coll right, left;
};

struct ask_s{
   coll radice, z;
   int size;
};



static coll NEWnode(AutorizzazioneSk val, coll right, coll left){
    coll x=malloc(sizeof(struct nodo));
    if(x==NULL) exit(EXIT_FAILURE);
    x->val=val;
    x->right=right;
    x->left=left;
    return x;
}

static AutorizzazioniSk BSTinit(){
    AutorizzazioniSk s;
    s=(AutorizzazioniSk)malloc(sizeof(struct ask_s));
    if(s==NULL) exit(EXIT_FAILURE);
    s->z=NEWnode(AUTORIZZAZIONESKsetNull(), NULL, NULL);
    s->radice=s->z;
    s->size=0;
    return s;
}


static AutorizzazioneSk *searchR(coll head, coll z, int sciatore){
    if(head==z)
        return NULL;
    if(sciatore<head->val.sciatore)
        return searchR(head->left, z, sciatore);
    else if (sciatore>head->val.sciatore)
        return searchR(head->right, z, sciatore);
    return &head->val;
}

static AutorizzazioneSk *BSTsearch(AutorizzazioniSk s, int sciatore){
    return searchR(s->radice, s->z, sciatore);
}


static coll insertR(coll head, coll z, AutorizzazioneSk as){
    if(head==z){
        return NEWnode(as, z, z);
    }
    if(as.sciatore<head->val.sciatore){
        head->left=insertR(head->left, z, as);
    }
    else if (as.sciatore>head->val.sciatore){
        head->right=insertR(head->right, z, as);
    }
    return head;
}

static void BSTinsertInLeaf(AutorizzazioniSk s, AutorizzazioneSk as){
    s->radice=insertR(s->radice, s->z, as);
    (s->size)++;
    return;
}


static void treeFree(coll head, coll z){
    if(head==z)
        return;
    treeFree(head->left, z);
    treeFree(head->right, z);
    free(head);
    return;
}

static void BSTfree(AutorizzazioniSk s){
    if(s!=NULL){
        treeFree(s->radice, s->z);
        free(s->z);
        free(s);
    }
    return;
}


AutorizzazioniSk AUTORIZZAZIONISKinit(){
    return BSTinit();
}


AutorizzazioneSk *AUTORIZZAZIONISKsearch(AutorizzazioniSk as, long sciatore){
    return BSTsearch(as, sciatore);
}


void AUTORIZZAZIONISKadd(AutorizzazioniSk as, AutorizzazioneSk a){
    BSTinsertInLeaf(as, a);
    (as->size)++;
    return;
}


int AUTORIZZAZIONISKsize(AutorizzazioniSk as){
    return as->size;
}


static void printR(coll head, coll z, FILE *f){
    if(head==z)
        return;
    printR(head->left, z, f);
    AUTORIZZAZIONESKprint(head->val, f);
    printR(head->right, z, f);
    return;
}

void AUTORIZZAZIONISKprint(AutorizzazioniSk as, FILE *f){
    printR(as->radice, as->z, f);
    return;
}


void AUTORIZZAZIONISKfree(AutorizzazioniSk as){
    BSTfree(as);
    return;
}
