#include "dipendenti.h"

struct dip{
    Dipendente  *dipendenti;
    int nDipendenti;
};

Dipendenti DIPENDENTIinit(int nDipendenti){
    Dipendenti d;
    d=(Dipendenti)malloc(sizeof(struct dip));
    if(d==NULL)
       exit(EXIT_FAILURE);
    d->nDipendenti=nDipendenti;
    d->dipendenti=(Dipendente*)malloc(nDipendenti*sizeof(Dipendente));
    if(d->dipendenti==NULL)
       exit(EXIT_FAILURE);
    return d;
}

Dipendenti DIPENDENTIread(FILE *f){
    int nDip, i;
    Dipendenti d;
    fscanf(f, "%d", &nDip);
    d=DIPENDENTIinit(nDip);
    for(i=0; i<nDip; i++)
       d->dipendenti[i]=DIPENDENTEread(f);
    return d;
}

Dipendente DIPENDENTIgetDipendente(Dipendenti d, int index){
    return d->dipendenti[index];
}

int DIPENDENTIsearch(Dipendenti d, int matricola){
    int i;
    for(i=0; i<d->nDipendenti; i++){
        if(d->dipendenti[i].matricola==matricola)
           return i;
    }
    return -1;
}

int DIPENDENTIsize(Dipendenti d){
    return d->nDipendenti;
}

void DIPENDENTIfree(Dipendenti d){
    if(d!=NULL){
       if(d->dipendenti!=NULL)
          free(d->dipendenti);
       free(d);
    }
    return;
}
