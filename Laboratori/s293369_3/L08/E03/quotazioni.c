//
// Created by simone on 08/12/22.
//

#include "quotazioni.h"

typedef struct BSTnode* link;
struct BSTnode { Quotazione item; link p; link l; link  r; int N; } ;
struct binarysearchtree { link root;  link z; };
static link NEW(Quotazione item, link p, link l, link r, int N);
static void treePrintR(link h, link z);
static void searchR(link h, Quotazione k, link z,BST bst);

void readbst(BST bstq,FILE *fp){
    Quotazione X;
    bstq=BSTinit();
    while(!feof(fp)){
        X=QuotazioneScan(fp);
        BSTsearch(bstq,X);
    }
    treePrintR(bstq->root,bstq->z);
}

void BSTinsert_leafI(BST bst, Quotazione x) {
    link p = bst->root, h = p;
    if (bst->root == bst->z) {
        bst->root = NEW(x, bst->z, bst->z, bst->z, x.quantitatransiozioni);
        return;
    }
    while (h != bst->z) {
        p = h;
        h->N++;
        h = (KEYcmp(KEYget(x.data), KEYget(h->item.data))==-1) ? h->l : h->r;
    }
    h = NEW(x, p, bst->z, bst->z, x.quantitatransiozioni);
    if (KEYcmp(KEYget(x.data), KEYget(p->item.data))==-1)
        p->l = h;
    else
        p->r = h;
}

Quotazione QuotazioneScan(FILE *fp){
    Quotazione val;
    char stringadata[11];
    fscanf(fp,"%s %*s %f %d",stringadata,&(val.valore),&(val.quantitatransiozioni));
    sscanf (stringadata,"%d/%d/%d", &val.data.anno,&val.data.mese,&val.data.giorno);
    return val;
}

BST BSTinit() {
    BST bst = malloc(sizeof *bst) ;
    bst->root = ( bst->z = NEW(QuotazionesetNull(), NULL, NULL, NULL, 0));
    return bst;
}

Quotazione QuotazionesetNull() {
    Quotazione val = {0,0,0,0,0};
    return val;
}

static link NEW(Quotazione item, link p, link l, link r, int N) {
    link x = malloc(sizeof *x);
    x->item = item; x->p = p; x->l = l; x->r = r; x->N = N;
    return x;
}

void QuotationStore(Quotazione val) {
    printf("year: %d month: %d day: %d value: %.2f number: %d\n", val.data.anno, val.data.mese,val.data.giorno,val.valore,val.quantitatransiozioni);
}

static void treePrintR(link h, link z) {
    if (h == z)
        return;
    treePrintR(h->l, z);
    QuotationStore(h->item);
    treePrintR(h->r, z);
}

static void searchR(link h, Quotazione k, link z,BST bst) {
    int cmp;
    if (h == z){
        BSTinsert_leafI(bst,k);
        return;
    }
    cmp = KEYcmp(KEYget(k.data), KEYget(h->item.data));
    if (cmp==0){
        //printf("nodo gia trovato, come lo modifico?\n");
        editnodebst(&(h->item),k);
        return;
    }
    if (cmp==-1)
        return searchR(h->l, k, z,bst);
    else
        return searchR(h->r, k, z,bst);
}

void BSTsearch(BST bst, Quotazione k) {
    searchR(bst->root, k, bst->z,bst);
}

void editnodebst(Quotazione *item, Quotazione k){
    float res;
    res =  (float)(( (item->valore * (float)item->quantitatransiozioni ) + (k.valore * (float)k.quantitatransiozioni)) / ((float)item->quantitatransiozioni + (float)k.quantitatransiozioni));
    item->quantitatransiozioni=item->quantitatransiozioni+k.quantitatransiozioni;
    item->valore=res;
}