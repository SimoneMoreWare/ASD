#include "divisione.h"
#include <math.h>
#define MAX 11

struct div{
    Requisito requisiti[MANSIONI];
    char sigla[MAX];
    Associazione *associazioni;
    int dimA, maxDimA;
    int compTot[MANSIONI], addTot[MANSIONI];
};

//Requisito
Requisito REQUISITOread(FILE *f){
    Requisito r;
    fscanf(f, "%d %d %d", &r.numMinAdd, &r.compMinTot, &r.compTotOtt);
    return r;
}

//Associazione
Associazione ASSOCIAZIONEcrea(Dipendente d, int mansione){
    Associazione a;
    a.dip=d;
    a.mansione=mansione;
    return a;
}

void ASSOCIAZIONEprint(Associazione a, FILE *f){
    char mans;
    switch(a.mansione){
       case OPERAIO:
          mans='o';
          break;
       case AMMINISTRATIVO:
          mans='a';
          break;
       case TECNICO:
          mans='t';
          break;
       case INFORMATICO:
          mans='i';
    }
    fprintf(f, "%d %c", a.dip.matricola, mans);
    return;
}

//Divisione
Divisione DIVISIONEinit(){
    Divisione d;
    int i;
    d=(Divisione)malloc(sizeof(struct div));
    if(d==NULL)
      exit(EXIT_FAILURE);
    d->dimA=0;
    d->maxDimA=1;
    d->associazioni=(Associazione*)malloc(d->maxDimA*sizeof(Associazione));
    if(d->associazioni==NULL)
       exit(EXIT_FAILURE);
    for(i=0; i<MANSIONI; i++){
       d->compTot[i]=0;
       d->addTot[i]=0;
    }
    return d;
}

Divisione DIVISIONEread(FILE *f){
    Divisione d;
    int i;
    d=DIVISIONEinit();
    fscanf(f, "%s", d->sigla);
    for(i=0; i<MANSIONI; i++)
       d->requisiti[i]=REQUISITOread(f);
    return d;
}

void DIVISIONEinsert(Divisione div, Dipendente dip, int mansione){
    if(div->maxDimA==div->dimA){
       div->maxDimA=2*div->maxDimA;
       div->associazioni=realloc(div->associazioni, div->maxDimA*sizeof(Associazione));
       if(div->associazioni==NULL)
          exit(EXIT_FAILURE);
    }
    div->associazioni[div->dimA]=ASSOCIAZIONEcrea(dip, mansione);
    (div->dimA)++;
    div->compTot[mansione]+=dip.competenze[mansione];
    (div->addTot[mansione])++;
    return;
}

void DIVISIONEprintAssociazioni(Divisione d, FILE *f){
    int i;
    for(i=0; i<d->dimA; i++){
       fprintf(f, "%s ", d->sigla);
       ASSOCIAZIONEprint(d->associazioni[i], f);
       fprintf(f, "\n");
    }
    return;
}

int DIVISIONEgetScostamento(Divisione d, int *compTot){
    int i, somma=0;
    for(i=0; i<MANSIONI; i++){
       somma=somma+abs(d->requisiti[i].compTotOtt - compTot[i]);
    }
    return somma;
}

Boolean DIVISIONEcheck(Divisione d, int *compTot, int* addTot){
    int i;
    for(i=0; i<MANSIONI; i++){
       if(compTot[i] < d->requisiti[i].compMinTot)
          return FALSO;
       if(addTot[i] < d->requisiti[i].numMinAdd)
          return FALSO;
    }
    return VERO;
}

char *DIVISIONEgetSigla(Divisione d){
    return d->sigla;
}

Divisione DIVISIONEsetNull(){
    return NULL;
}

Boolean DIVISIONEisEmpty(Divisione d){
    if(d==NULL)
       return VERO;
    return FALSO;
}

void DIVISIONEfree(Divisione d){
    if(d!=NULL){
       if(d->associazioni!=NULL)
          free(d->associazioni);
       free(d);
    }
    return;
}
