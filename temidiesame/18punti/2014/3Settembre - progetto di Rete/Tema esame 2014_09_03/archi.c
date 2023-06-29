#include "archi.h"

struct archi{
   Edge *edges;
   int dim, maxD;
};



Archi ARCHIinit(){
   Archi a;
   a=(Archi)malloc(sizeof(struct archi));
   if(a==NULL) exit(EXIT_FAILURE);
   a->dim=0;
   a->maxD=1;
   a->edges=(Edge*)malloc(a->maxD*sizeof(Edge));
   if(a->edges==NULL) exit(EXIT_FAILURE);
   return a;
}


void ARCHIinsert(Archi a, Edge e){
   if(a->dim==a->maxD){
      a->maxD=2*a->maxD;
      a->edges=realloc(a->edges, a->maxD*sizeof(Edge));
      if(a->edges==NULL) exit(EXIT_FAILURE);
   }
   a->edges[a->dim]=e;
   (a->dim)++;
   return;
}


Edge *ARCHIgetArchi(Archi a){
   return a->edges;
}


int ARCHIsize(Archi a){
   return a->dim;
}


void ARCHIfree(Archi a){
   if(a!=NULL){
      if(a->edges!=NULL)
         free(a->edges);
      free(a);
   }
   return;
}
