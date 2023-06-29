#include "produttore.h"

struct prod_s{
    char nome[MAX];
    Modelli modelli;
};


Produttore PRODUTTOREinit(){
    Produttore p;
    p=(Produttore)malloc(sizeof(struct prod_s));
    if(p==NULL) exit(EXIT_FAILURE);
    p->modelli=MODELLIinit();
    return p;
}


Produttore PRODUTTOREread(FILE *f){
    Produttore p=PRODUTTOREinit();
    char nomeFile[MAX];
    FILE *fi;
    if(fscanf(f, "%s %s", p->nome, nomeFile)==2){
       fi=fopen(nomeFile, "r");
       if(fi==NULL) exit(EXIT_FAILURE);
       p->modelli=MODELLIread(fi);
       return p;
    }
    return PRODUTTOREsetNull();
}


void PRODUTTOREprint(Produttore p, FILE *f){
    fprintf(f, "%s\n", p->nome);
    fprintf(f,"\t---MODELLI---\n");
    if(MODELLIsize(p->modelli)>0){
       MODELLIprint(p->modelli, f);
    }
    else{
       fprintf(f, "\tNessun modello presente.\n");
    }
    return;
}


Produttore PRODUTTOREsetNull(){
    return NULL;
}


Boolean PRODUTTOREisNull(Produttore p){
    if(p==NULL)
      return VERO;
    return FALSO;
}


void PRODUTTOREaccorpaProduttori(Produttore p1, Produttore p2){
    MODELLIspostaModelli(p1->modelli, p2->modelli);
    return;
}


char *PRODUTTOREgetNome(Produttore p){
    return p->nome;
}


Modelli PRODUTTOREgetModelli(Produttore p){
    return p->modelli;
}


void PRODUTTOREfree(Produttore p){
    if(p!=NULL){
       MODELLIfree(p->modelli);
       free(p);
    }
    return;
}
