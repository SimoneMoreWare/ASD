#include "tokenbonus.h"

TokenBonus TOKENBONUSread(FILE *f){
   TokenBonus tb;
   int i;
   fscanf(f, "%d %d", &tb.dim, &tb.bonus);
   tb.t=(Token*)malloc(tb.dim*sizeof(Token));
   if(tb.t==NULL) exit(EXIT_FAILURE);
   for(i=0; i<tb.dim;i++){
      tb.t[i]=TOKENread(f);
   }
   return tb;
}


void TOKENBONUSclear(TokenBonus *tb){
   if(tb->t!=NULL)
      free(tb->t);
   return;
}
