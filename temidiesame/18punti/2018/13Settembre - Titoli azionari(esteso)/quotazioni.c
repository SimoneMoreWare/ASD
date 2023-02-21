//
// Created by gabbi on 03/01/2020.
//

#include "quotazioni.h"

typedef struct nodo_ *link;

struct nodo_{
    quotazione q;
    link l,r;
    int n;
};

struct BSTquotazioni_{
    link root;
    int count;
};

BSTquotazioni BSTquotazioneInit(){
    BSTquotazioni bst;
    bst = malloc(sizeof(*bst));
    bst->root = NULL;
    bst->count = 0;
    return bst;
}

int BSTquotazioniEmpty(BSTquotazioni bst){
    return bst->root == NULL || bst->count == 0;
}

static link NEW(data_t d, float val, int qta, link l, link r){
    link x;
    x = malloc(sizeof(*l));
    x->q.data = d;
    x->q.val = val*(float)qta;
    x->q.q = qta;
    x->l = l;
    x->r = r;
    x->n = 1;
    return x;
}

static link insertR(link root, data_t d, float val, int qta){
    link h;
    if(root == NULL) {
        h = NEW(d, val, qta, NULL, NULL);
        return h;
    }
    if(datacmp(d,quotazioneGetData(root->q))<0)
        root->l = insertR(root->l,d,val,qta);
    else if(datacmp(d,quotazioneGetData(root->q))>0)
        root->r = insertR(root->r,d,val,qta);
    else{
        root->q.val += qta*val;
        root->q.q += qta;
    }
    (root->n)++;
    return root;
}
void BSTquotazioniInsert(BSTquotazioni bst, data_t d, float val, int q){
    bst->root = insertR(bst->root,d,val,q);
    bst->count++;
}

static quotazione searchR(link root, data_t d){
    int cmp;
    if(root == NULL)
        return quotazioneSetNull();
    cmp = datacmp(d, root->q.data);
    if(cmp == 0)
        return root->q;
    else if(cmp < 0)
        return searchR(root->l,d);
    else
        return searchR(root->r, d);
}

quotazione BSTquotazioniSearch(BSTquotazioni bst, data_t d){
    return searchR(bst->root, d);
}

static void minmaxR(link h, float* min, float* max){
    float val = quotazioneGetVal(h->q);
    if(h == NULL)
        return;
    if(*min < 0 || val < *min)
        *min = val;
    if(*max < 0 || val > *max)
        *max = val;
    if(h->l)
        minmaxR(h->l, min, max);
    if(h->r)
        minmaxR(h->r, min, max);
}

void BSTquotazioniGetMinMax(BSTquotazioni bst, float *min, float *max){
    if(BSTquotazioniEmpty(bst))
        return;
    minmaxR(bst->root, min, max);
}

static void treePrint(FILE *out, link root){
    if(root == NULL)
        return;
    treePrint(out, root->l);
    quotazioneStore(out, root->q);
    treePrint(out, root->r);
}

void BSTquotazioniStore(FILE *out, BSTquotazioni bst){
    if(bst->root == NULL)
        return;
    treePrint(out,bst->root);
}

void minMaxRangeR(link root, float *min, float *max, data_t d1, data_t d2){
    float val;
    int cmp1,cmp2;
    if(root == NULL)
        return;
    cmp1 = datacmp(d1, quotazioneGetData(root->q));
    cmp2 = datacmp(d2, quotazioneGetData(root->q));
    if(cmp1 < 0)
        minMaxRangeR(root->l, min, max, d1, d2);
    if(cmp2 > 0)
        minMaxRangeR(root->r, min, max, d1, d2);

    if(cmp1 <= 0 && cmp2 >= 0){
        val = quotazioneGetVal(root->q);
        if(*min < 0 || val < *min)
            *min = val;
        if(*max < 0 || val > *max)
            *max = val;
    }
}

void BSTquotazioniGetMinMaxRange(BSTquotazioni bst, float *min, float *max, data_t d1, data_t d2){
    if(BSTquotazioniEmpty(bst))
        return;
    minMaxRangeR(bst->root, min, max, d1, d2);
}

data_t BSTgetMindata(BSTquotazioni bst){
    link x;
    for(x=bst->root; x->l != NULL; x=x->l);
    return x->q.data;
}

data_t BSTgetMaxdata(BSTquotazioni bst){
    link x;
    for(x=bst->root; x->r != NULL; x=x->r);
    return x->q.data;
}

static link rotR(link h){
    link x = h->l;
    h->l = x->r;
    x->r = h;
    x->n = h->n;
    h->n = 1;
    h->n += (h->l) ? h->l->n : 0;
    h->n += (h->r) ? h->r->n : 0;
    return x;
}

static link rotL(link h){
    link x = h->r;
    h->r = x->l;
    x->l = h;
    x->n = h->n;
    h->n = 1;
    h->n += (h->l) ? h->l->n : 0;
    h->n += (h->r) ? h->r->n : 0;
    return x;
}

static link partR(link h, int r){
    int t = h->l->n;
    if(t>r){
        h->l = partR(h->l, r);
        h = rotR(h);
    }
    if(t<r){
        h->r = partR(h->r, r-t-1);
        h = rotL(h);
    }
    return h;
}

static link balanceR(link h){
    int r;
    if(h == NULL)
        return NULL;
    r = (h->n+1)/2-1;
    h = partR(h,r);
    h->l = balanceR(h->l);
    h->r = balanceR(h->r);
    return h;
}

void BSTbalance(BSTquotazioni bst){
    bst->root = balanceR(bst->root);
}

static int camminoMinR(link h, int dpth){
    int minl, minr;
    if(h == NULL)
        return 0;
    if(h->l == NULL && h->r == NULL)
        return 1;
    minl = camminoMinR(h->l, dpth+1);
    minr = camminoMinR(h->r, dpth+1);
    if(h->l == NULL)
        return minr+1;
    if(h->r == NULL)
        return minl+1;
    if(minl < minr)
        return minl+1;
    else
        return minr+1;
}

static void camminoMaxR(link h, int dpth, int *max){
    if(h==NULL)
        return;
    if(h->l == NULL && h->r == NULL){
        if(dpth > *max)
            *max = dpth;
    }
    camminoMaxR(h->l, dpth+1, max);
    camminoMaxR(h->r, dpth+1, max);
}


int BSTgetDiff(BSTquotazioni bst){
    int min=0,max=0;
    min = camminoMinR(bst->root, 1);
    camminoMaxR(bst->root,1, &max);
    return max-min;
}