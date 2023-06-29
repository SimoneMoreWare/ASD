#include "articoli.h"

struct articoli_s{
    Articolo *articoli;
    int dim;
};

Articoli ARTICOLIinit(int nArticoli){
    Articoli a;
    a=(Articoli)malloc(sizeof(struct articoli_s));
    if(a==NULL)
        exit(EXIT_FAILURE);
    a->dim=nArticoli;
    a->articoli=(Articolo*)malloc(a->dim*sizeof(Articolo));
    if(a->articoli==NULL)
        exit(EXIT_FAILURE);
    return a;
}

Articoli ARTICOLIread(FILE *f){
    int nArticoli, i;
    Articoli a;
    fscanf(f, "%d", &nArticoli);
    a=ARTICOLIinit(nArticoli);

    for(i=0; i<nArticoli; i++){
        a->articoli[i]=ARTICOLOread(f);
    }
    return a;
}

Articolo ARTICOLIgetArticolo(Articoli a, int index){
    return a->articoli[index];
}

int ARTICOLIgetNumArticoli(Articoli a){
    return a->dim;
}

ST ARTICOLIgetArgomenti(Articoli a){
    ST argomenti=STinit(1);
    Articolo ar;
    int i, id;

    for(i=0; i<a->dim; i++){
        ar=ARTICOLIgetArticolo(a, i);
        id=STsearch(argomenti, ar.argomento);
        if(id==-1){
            STinsert(argomenti, ARGOMENTOcrea(ar.argomento));
        }
    }
    return argomenti;
}

void ARTICOLIfree(Articoli a){
    if(a!=NULL){
        if(a->articoli!=NULL)
             free(a->articoli);
        free(a);
    }
    return;
}
