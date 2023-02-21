#include <stdio.h>
#include <stdlib.h>
#define DIM 8

typedef struct nodo *link;

struct nodo{
int nodo_val;
link nodo_prox;
};

typedef struct lista_{
link nodo_testa;
}lista_t;

link Crea_Nodo(int val,link h){
link x=malloc(sizeof(link));
if(x==NULL){
    return NULL;
    }
x->nodo_val=val;
x->nodo_prox=h;
return x;
}

lista_t *Crea_Lista(){
lista_t *l=malloc(sizeof(lista_t));
if(l==NULL){
    return NULL;
    }
l->nodo_testa=NULL;
return l;
}

void Stampa_Lista(lista_t *l){
link x;
for(x=l->nodo_testa;x!=NULL;x=x->nodo_prox){
    printf("%d\n",x->nodo_val);
    }
}

void Inserimento_Lista(int v,lista_t *l){
link tp;
if(l->nodo_testa==NULL){
    l->nodo_testa=Crea_Nodo(v,NULL);
    tp=l->nodo_testa;
    }else{
    tp->nodo_prox=Crea_Nodo(v,NULL);
    tp=tp->nodo_prox;
    }
}

lista_t *split_list(int n,lista_t *L0,lista_t **L2){
lista_t *L1=Crea_Lista();
if(L1==NULL){
    return NULL;
}
link x,tp;
for(x=L0->nodo_testa;x!=NULL;x=x->nodo_prox){
    if((x->nodo_val)<n){
        Inserimento_Lista(x->nodo_val,L1);
        }
    }
for(x=L0->nodo_testa;x!=NULL;x=x->nodo_prox){
    if((x->nodo_val)>=n){
        if((*L2)->nodo_testa==NULL){
            (*L2)->nodo_testa=Crea_Nodo(x->nodo_val,NULL);
            tp=(*L2)->nodo_testa;
            }else{
            tp->nodo_prox=Crea_Nodo(x->nodo_val,NULL);
            tp=tp->nodo_prox;
            }
        }
    }
return L1;
}

int main()
{
    int i,v[DIM]={7,8,25,2,9,-5,10,37};
    lista_t *L0,*L1,*L2;

    L0=Crea_Lista();
    L1=Crea_Lista();
    L2=Crea_Lista();
    if(L0==NULL || L1==NULL || L2==NULL){
        return NULL;
    }

    for(i=0;i<DIM;i++){
    Inserimento_Lista(v[i],L0);
    }

    printf("-->STAMPA_LISTA_0\n");
    Stampa_Lista(L0);

    L1=split_list(18,L0,&L2);

    printf("-->STAMPA_LISTA_1\n");
    Stampa_Lista(L1);
    printf("-->STAMPA_LISTA_2\n");
    Stampa_Lista(L2);
    return 0;
}
