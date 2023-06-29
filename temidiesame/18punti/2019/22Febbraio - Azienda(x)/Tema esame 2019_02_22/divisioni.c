#include "divisioni.h"
#include <string.h>

struct divs{
    Divisione *divisioni;
    int nDivisioni;
};

Divisioni DIVISIONIinit(int nDiv){
    Divisioni d;
    d=(Divisioni)malloc(sizeof(struct divs));
    if(d==NULL)
       exit(EXIT_FAILURE);
    d->nDivisioni=nDiv;
    d->divisioni=(Divisione*)malloc(sizeof(Divisione));
    if(d->divisioni==NULL)
       exit(EXIT_FAILURE);
    return d;
}

Divisioni DIVISIONIread(FILE *f){
    int i, nDiv;
    Divisioni d;
    fscanf(f, "%d", &nDiv);
    d=DIVISIONIinit(nDiv);
    for(i=0; i<nDiv; i++)
       d->divisioni[i]=DIVISIONEread(f);
    return d;
}

Divisione DIVISIONIgetDivisione(Divisioni d, int index){
    return d->divisioni[index];
}

int DIVISIONIsearch(Divisioni d, char *sigla){
    int i;
    for(i=0; i<d->nDivisioni; i++){
       if(strcmp(sigla, DIVISIONEgetSigla(d->divisioni[i]))==0)
          return i;
    }
    return -1;
}

float DIVISIONIscostamentoMedio(Divisioni d, int **compTot){
    float scostamento;
    int somma=0, i;
    for(i=0; i<d->nDivisioni; i++){
       somma=somma+DIVISIONEgetScostamento(d->divisioni[i], compTot[i]);
    }
    scostamento=(float)somma/(float)d->nDivisioni;
    return scostamento;
}

Boolean DIVISIONIcheck(Divisioni d, int **compTot, int **addTot){
    int i;
    for(i=0; i<d->nDivisioni; i++){
       if(DIVISIONEcheck(d->divisioni[i], compTot[i], addTot[i])==FALSO)
          return FALSO;
    }
    return VERO;
}

int DIVISIONIsize(Divisioni d){
    return d->nDivisioni;
}

void DIVISIONIfree(Divisioni d){
    int i;
    if(d!=NULL){
       if(d->divisioni!=NULL){
          for(i=0; i<d->nDivisioni; i++)
             DIVISIONEfree(d->divisioni[i]);
          free(d->divisioni);
       }
       free(d);
    }
    return;
}


void DIVISIONIprintAssociazioni(Divisioni d, FILE *f){
    int i;
    for(i=0; i<d->nDivisioni; i++)
       DIVISIONEprintAssociazioni(d->divisioni[i], f);
    return;
}
