#include "piatti.h"

struct piatti_s{
    Piatto *piatti;
    int nPiatti;
};



Piatti PIATTIinit(int dim){
    Piatti p;
    p=(Piatti)malloc(sizeof(struct piatti_s));
    if(p==NULL)
        exit(EXIT_FAILURE);
    p->nPiatti=dim;
    p->piatti=(Piatto*)malloc(dim*sizeof(Piatto));
    if(p->piatti==NULL)
       exit(EXIT_FAILURE);
    return p;
}


Piatti PIATTIread(FILE *f){
    int nPiatti, i;
    Piatti p;
    fscanf(f, "%d", &nPiatti);
    p=PIATTIinit(nPiatti);
    for(i=0; i<nPiatti; i++)
       p->piatti[i]=PIATTOread(f);
    return p;
}


void PIATTIprint(Piatti p, FILE *f){
    int i;
    for(i=0; i<p->nPiatti; i++)
       PIATTOprint(p->piatti[i], f);
    return;
}


Piatto PIATTIgetPiatto(Piatti p, int index){
    return p->piatti[index];
}


int PIATTIsize(Piatti p){
    return p->nPiatti;
}


void PIATTIfree(Piatti p){
    if(p!=NULL){
        if(p->piatti!=NULL)
            free(p->piatti);
        free(p);
    }
    return;
}
