#include "cicli.h"

struct cicli{
	int nCicli, maxD;
      Ciclo *cicli;
};

Cicli CICLIinit(){
	Cicli c;
      c=(Cicli)malloc(sizeof(struct cicli));
      if(c==NULL) exit(EXIT_FAILURE);
      c->nCicli=0;
      c->maxD=1;
      c->cicli=(Ciclo*)malloc(c->maxD*sizeof(Ciclo));
      if(c->cicli==NULL) exit(EXIT_FAILURE);
      return c;
}

void CICLIinsert(Cicli c, Ciclo ci){
     if(c->nCicli==c->maxD){
         c->maxD=2*c->maxD;
         c->cicli=realloc(c->cicli, c->maxD*sizeof(Ciclo));
         if(c->cicli==NULL) exit(EXIT_FAILURE);
     }
     c->cicli[c->nCicli]=ci;
     (c->nCicli)++;
    return;
}

Ciclo CICLIgetCiclo(Cicli c, int index){
      return c->cicli[index];
}

int CICLIgetNumCicli(Cicli c){
     return c->nCicli;
}

Cicli CICLIread(FILE *f){
     Cicli c=CICLIinit();
     Ciclo ci;
     ci=CICLOread(f);
     while(CICLOisNull(ci)==FALSO){
          CICLIinsert(c, ci);
          ci=CICLOread(f);
     }
     return c;
}

void CICLIfree(Cicli c){
     if(c!=NULL){
         if(c->cicli!=NULL){
             free(c->cicli);
         }
         free(c);
     }
}
