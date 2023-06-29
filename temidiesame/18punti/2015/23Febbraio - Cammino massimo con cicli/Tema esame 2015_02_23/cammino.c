#include "cammino.h"

Cammino CAMMINOread(ST table, FILE *f){
   Cammino c;
   int i, lun;
   char label[MAX];
   fscanf(f, "%d", &lun);
   c.dim=lun+1;
   c.vertici=(int*)malloc(c.dim*sizeof(int));
   if(c.vertici==NULL) exit(EXIT_FAILURE);
   for(i=0; i<c.dim; i++){
      fscanf(f, "%s", label);
      c.vertici[i]=STsearch(table, label);
   }
   return c;
}


Cammino CAMMINOcrea(int max){
   Cammino c;
   c.maxD=max;
   c.dim=0;
   c.vertici=(int*)malloc(max*sizeof(int));
   if(c.vertici==NULL) exit(EXIT_FAILURE);
   return c;
}


void CAMMINOinsert(Cammino *c, int v){
   if(c->maxD==c->dim){
      c->maxD=2*c->maxD;
      c->vertici=realloc(c->vertici, c->maxD*sizeof(int));
      if(c->vertici==NULL) exit(EXIT_FAILURE);
   }
   c->vertici[c->dim]=v;
   (c->dim)++;
   return;
}


void CAMMINOelimina(Cammino *c){
   (c->dim)--;
   return;
}


static int min(int a, int b){
   if(a<b)
      return a;
   return b;
}

int *CAMMINOintersezione(Cammino c1, Cammino c2, int *dim){
   int *intersezione, i, j, index=0;
   intersezione=(int*)malloc(min(c1.dim, c2.dim)*sizeof(int));
   if(intersezione==NULL) exit(EXIT_FAILURE);
   for(i=0; i<c1.dim; i++){
      for(j=0; j<c2.dim; j++){
         if(c1.vertici[i]==c2.vertici[j])
            intersezione[index++]=c1.vertici[i];
      }
   }
   *dim=index;
   return intersezione;
}


void CAMMINOstampaSottocammini(Cammino c, int *intersezione, int dim, ST table, FILE *f){
   int i, j, condizione;
   Vertice v;
   for(i=0; i<dim; i++){
      fprintf(f, "\tSottocammino %d: ", i+1);
      for(j=0; intersezione[i]!=c.vertici[j] && j<c.dim; j++);
      if(i<(dim-1)){
         condizione=(c.vertici[j]!=intersezione[i+1] && j<c.dim);
      }
      else
         condizione=(j<c.dim);
      while(condizione){
         v=STgetVerticeByIndex(table, c.vertici[j]);
         fprintf(f, "%s ", v.nome);
         j++;
         if(i<(dim-1))
            condizione=(c.vertici[j]!=intersezione[i+1] && j<c.dim);
         else
            condizione=(j<c.dim);
      }
      if(i<dim-1){
         v=STgetVerticeByIndex(table, c.vertici[j]);
         fprintf(f, "%s", v.nome);
      }
      fprintf(f, "\n");
   }
   return;
}


void CAMMINOstampa(Cammino c,  ST table, FILE *f){
   int i;
   Vertice v;
   for(i=0; i<c.dim; i++){
      v=STgetVerticeByIndex(table, c.vertici[i]);
      fprintf(f, "%s ", v.nome);
   }
   return;
}


void CAMMINOclear(Cammino *c){
   if(c->vertici!=NULL)
      free(c->vertici);
   return;
}
