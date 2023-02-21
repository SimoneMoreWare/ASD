#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 30

typedef struct nodo *link,node_t;

struct nodo{
char *str;
link prox_nodo;
};

link Crea_Nodo(char *s,link h){
link x=malloc(sizeof(link));
if(x==NULL){
    return NULL;
    }
x->str=strdup(s);
x->prox_nodo=h;
return x;
}

node_t *inserimento_coda(char *s,link h){
link x;
if(h==NULL){
    h=Crea_Nodo(s,NULL);
    return h;
    }
    for(x=h;x->prox_nodo!=NULL;x=x->prox_nodo);
    x->prox_nodo=Crea_Nodo(s,NULL);
return h;
}

void Stampa(link h){
link x;
for(x=h;x!=NULL;x=x->prox_nodo){
    printf("%s\n",x->str);
    }
}

node_t *splitStr(char *str){
int i,j,dim_str=strlen(str);
char *str_tmp;
link h=NULL;

for(i=dim_str-1;i>=0;i--){
    if(str[i]=='.'){
        str[i]='\0';
        j=i+1;
        str_tmp=strdup(str+j);
        h=inserimento_coda(str_tmp,h);
        }
    if(i==0){
        str_tmp=strdup(str+i);
        h=inserimento_coda(str_tmp,h);
        }
    }
return h;
}

int main(){
char str[DIM]={"a.bb.ccc.dddd.eeeee.fffff"};
link h;
h=splitStr(str);
Stampa(h);
return 0;
}
