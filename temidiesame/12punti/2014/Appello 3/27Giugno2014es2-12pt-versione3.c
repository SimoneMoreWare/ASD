#include <stdio.h>
#include <stdlib.h>

typedef struct nodo *link,nodo_t;

struct nodo{
int nodo_chiave;
nodo_t *prox_nodo;
nodo_t *prec_nodo;
};

typedef struct{
nodo_t *head;
nodo_t *tail;
}list_t;

nodo_t *Crea_Nodo(int chiave,nodo_t *prec,nodo_t *next){
nodo_t *x=malloc(sizeof(nodo_t));
if(x==NULL){
    return NULL;
    }
x->nodo_chiave=chiave;
x->prox_nodo=next;
x->prec_nodo=prec;
return x;
}

list_t *Crea_Lista(){
list_t *l=malloc(sizeof(list_t));
if(l==NULL){
    return NULL;
    }
l->head=NULL;
l->tail=NULL;
return l;
}

list_t *inserimento_da_testa_V1(list_t *l,int val){
nodo_t *p;
if(l->head==NULL){
    printf("[MODO_0]\n");
    l->head=Crea_Nodo(val,NULL,NULL);
    l->tail=l->head;
    }else{
    printf("[MODO_1]\n");
    p=l->tail;
    l->tail->prox_nodo=Crea_Nodo(val,p,NULL);
    l->tail=l->tail->prox_nodo;
    }
return l;
}

void inserimento_da_testa_V2(list_t **l,int val,link *tp,link *h){
link p;
if((*l)->head==NULL){
    printf("[MODO_0]\n");
    (*l)->head=Crea_Nodo(val,NULL,NULL);
    (*h)=(*l)->head;
    *tp=*h;
    }else{
    printf("[MODO_1]\n");
    p=(*tp);
    (*tp)->prox_nodo=Crea_Nodo(val,p,NULL);
    (*tp)=(*tp)->prox_nodo;
    }
}

void inserimento_da_testa_V3(list_t *l,int val){
link n,tp,h,p;
if(l->head==NULL){
    printf("-->[MODO_0]\n");
    l->head=Crea_Nodo(val,NULL,NULL);
    h=l->head;
    l->tail=h;
    tp=l->tail;
    printf("[MODO_0] TESTA=%d , CODA=%d\n",h->nodo_chiave,tp->nodo_chiave);
    }else{
    printf("-->[MODO_1]\n");
    p=l->tail;
    n=Crea_Nodo(val,p,NULL);
    l->tail->prox_nodo=n;
    l->tail=l->tail->prox_nodo;
    tp=l->tail;
    printf("[MODO_1] CODA=%d\n",tp->nodo_chiave);
    }
}

void inserimento_da_coda(list_t *l,int val){
link x,n,tp,p;
if(l->tail==NULL){
    printf("-->[MODO_0]\n");
    l->tail=Crea_Nodo(val,NULL,NULL);
    l->head=l->tail;
    }else{
    printf("-->[MODO_1]\n");
    tp=l->head;
    n=Crea_Nodo(val,NULL,tp);
    x=l->head->prec_nodo=n;
    l->head=x;
    p=l->head;
    }
}

void stampa_da_testa(list_t *l){
nodo_t *x;
for(x=l->head;x!=NULL;x=x->prox_nodo){
    printf("%d\n",x->nodo_chiave);
    }
}

void stampa_da_coda(list_t *l){
nodo_t *x=l->tail;
while(x!=NULL){
    printf("%d\n",x->nodo_chiave);
    x=x->prec_nodo;
    }
return;
}

void list_insert(list_t *l,int chiave,int estremo){
link tp,h=NULL;
if(estremo==0){
    inserimento_da_testa_V3(l,chiave);
    }else if(estremo==1){
    inserimento_da_coda(l,chiave);
    }
return;
}

void list_display(list_t *l,int modo){
if(modo==0){
    stampa_da_testa(l);
    }else if(modo==1){
    stampa_da_coda(l);
    }
return;
}

int main(){
list_t *L0=Crea_Lista();
list_t *L1=Crea_Lista();
if(L0==NULL || L1==NULL){
    return NULL;
}

list_insert(L0,5,0);
list_insert(L0,6,0);
list_insert(L0,7,0);
printf("[estremo_0]->[LISTA_DA_TESTA_OTTENUTA]\n");
list_display(L0,0);
printf("[estremo_0]->[LISTA_DA_CODA_OTTENUTA]\n");
list_display(L0,1);
printf("-----\n");

list_insert(L1,10,1);
list_insert(L1,9,1);
list_insert(L1,8,1);
printf("[estremo_1]->[LISTA_DA_TESTA_OTTENUTA]\n");
list_display(L1,0);
printf("[estremo_1]->[LISTA_DA_CODA_OTTENUTA]\n");
list_display(L1,1);
return 0;
}
