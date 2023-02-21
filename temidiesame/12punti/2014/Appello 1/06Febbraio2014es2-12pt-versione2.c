#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 10

typedef struct nodo *link;

struct nodo{
char *nodo_nome,*nodo_cognome;
link prox_nodo;
};

typedef struct lista_{
link nodo_testa;
}lista_t;

link Crea_Nodo(char *cognome,char *nome,link h){
link x=malloc(sizeof(link));
if(x==NULL){
    return NULL;
}
x->nodo_nome=strdup(nome);
x->nodo_cognome=strdup(cognome);
x->prox_nodo=h;
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
link x=l->nodo_testa;
while(x!=NULL){
    printf("cognome->%s , nome->%s\n",x->nodo_cognome,x->nodo_nome);
    x=x->prox_nodo;
    }
}

int controllo_nome(char *nome_A,char *nome_B){
int ris=strcmp(nome_A,nome_B);
return ris;
}

void inserimento_mio(lista_t *l,link p,link x,char *cognome,char *nome){
link n,tp;
if(p==NULL){
    n=Crea_Nodo(cognome,nome,x);
    l->nodo_testa=n;
    }else{
    tp=x;
    n=Crea_Nodo(cognome,nome,tp);
    p->prox_nodo=n;
    }
}

int inserisciInOrdine_V2(lista_t *lista,char *cognome,char *nome){
int VERO=1,FALSO=0;
link x,p;
int ris=-1;
if(lista->nodo_testa==NULL){
    lista->nodo_testa=Crea_Nodo(cognome,nome,NULL);
    return VERO;
}
/*Ho aggiunto ---> && strcmp(x->nodo_cognome,cognome)<=0 <---*/
/*Il (<=) permette di gestire sia strcmp<0 e ==0,in modo da gestire l'inserimento nell'ultimo nodo NULL e
l' eventuale --->strcmp(x->nodo_cognome,cognome)>0 <--- con le sole linee 84 e 85 .Sto usando il metodo Cumani.*/
for(x=lista->nodo_testa,p=NULL;x!=NULL && strcmp(x->nodo_cognome,cognome)<=0;p=x,x=x->prox_nodo){
    if(strcmp(x->nodo_cognome,cognome)==0){
        ris=controllo_nome(x->nodo_nome,nome);
        if(ris>0){
            inserimento_mio(lista,p,x,cognome,nome);
            return VERO;
        }else if(ris==0){
            return FALSO;
            }
        }
    }
    inserimento_mio(lista,p,x,cognome,nome);
    return VERO;
}


void Wrap_MIA(lista_t *l,char *cognome,char *nome){
int ris=-1;
ris=inserisciInOrdine_V2(l,cognome,nome);
if(ris==1){
printf("VERO\n");
}else
printf("FALSO\n");
return;
}

int main()
{
    char cognome_1[DIM]="f";
    char cognome_2[DIM]="a";
    char cognome_3[DIM]="a";
    char cognome_4[DIM]="a";
    char cognome_5[DIM]="a";

    char nome_1[DIM]="f";
    char nome_2[DIM]="b";
    char nome_3[DIM]="f";
    char nome_4[DIM]="b";
    char nome_5[DIM]="c";

    lista_t *l;

    l=Crea_Lista();
    if(l==NULL){
        return NULL;
    }else{
    printf("-->CHIAMATA_1\n");
    Wrap_MIA(l,cognome_1,nome_1);
    printf("-->CHIAMATA_2\n");
    Wrap_MIA(l,cognome_2,nome_2);
    printf("-->CHIAMATA_3\n");
    Wrap_MIA(l,cognome_3,nome_3);
    printf("-->CHIAMATA_4\n");
    Wrap_MIA(l,cognome_4,nome_4);
    printf("-->CHIAMATA_5\n");
    Wrap_MIA(l,cognome_5,nome_5);
    }
    printf("-->STAMPA_LISTA<--\n");
    Stampa_Lista(l);
    return 0;
}
