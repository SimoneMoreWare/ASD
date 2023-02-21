#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo *link;

struct nodo{
int nodo_val;
link l,r,p;
int nodo_figli;
int nodo_livello;
char *nodo_str;
};

link Crea_Nodo(int val,link sx,link dx,link padre,int figli,int livello,char *str){
link x=malloc(sizeof(*x));
x->nodo_val=val;
x->l=sx;
x->r=dx;
x->p=padre;
x->nodo_figli=figli;
x->nodo_livello=livello;
x->nodo_str=strdup(str);
return x;
}

link inserimento_nodi_BST(link h,link s,int val,int liv,char *str){
if(h==s){
h=Crea_Nodo(val,NULL,NULL,NULL,0,liv,str);
h->p=h;/*Lo faccio perché la radice del BST ha come padre se stesso,altrimenti (stampa_BST) da errore*/
return h;
    }
if(val<=h->nodo_val){
h->l=inserimento_nodi_BST(h->l,s,val,liv+1,str);
}else if(val>h->nodo_val){
h->r=inserimento_nodi_BST(h->r,s,val,liv+1,str);
}
return h;
}

/*INIZIO->FUNZIONE_RICORSIVA*/

void processTree(link root){
link tp;
if(root==NULL){
return;
}
processTree(root->l);
if(root->l!=NULL){
for(tp=root->l;tp!=NULL;tp=tp->r){
    (root->nodo_figli)++;
    tp->p=root;
        }
    }
processTree(root->r);
}

/*FINE->FUNZIONE_RICORSIVA*/

void stampa_BST(link h,link s){
if(h==s){
return;
    }
printf("nodo_str->%s , figli->%d , nodo_padre->%s\n",h->nodo_str,h->nodo_figli,h->p->nodo_str);
stampa_BST(h->l,s);
stampa_BST(h->r,s);
}

int main()
{
link rad=NULL;
rad=inserimento_nodi_BST(rad,NULL,15,0,"a");
rad=inserimento_nodi_BST(rad,NULL,9,0,"b");
rad=inserimento_nodi_BST(rad,NULL,10,0,"c");
rad=inserimento_nodi_BST(rad,NULL,13,0,"d");
rad=inserimento_nodi_BST(rad,NULL,11,0,"f");
rad=inserimento_nodi_BST(rad,NULL,12,0,"g");
rad=inserimento_nodi_BST(rad,NULL,8,0,"e");
rad=inserimento_nodi_BST(rad,NULL,5,0,"h");
rad=inserimento_nodi_BST(rad,NULL,6,0,"i");
rad=inserimento_nodi_BST(rad,NULL,7,0,"j");
processTree(rad);
stampa_BST(rad,NULL);
return 0;
}
