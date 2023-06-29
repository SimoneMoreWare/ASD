#include "bonus.h"

Bonus BONUSread(FILE *f){
   Bonus b;
   int i;
   fscanf(f, "%d", &b.dim);
   b.tbonus=(TokenBonus*)malloc(b.dim*sizeof(TokenBonus));
   if(b.tbonus==NULL) exit(EXIT_FAILURE);
   for(i=0; i<b.dim; i++){
      b.tbonus[i]=TOKENBONUSread(f);
   }
   return b;
}


void BONUSclear(Bonus *b){
   if(b->tbonus!=NULL)
      free(b->tbonus);
}
