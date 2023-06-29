#include "categorie.h"

struct cats{
   Categoria categorie[100];
   int size;
};



Categorie CATEGORIEinit(){
   Categorie c;
   c=(Categorie)malloc(sizeof(struct cats));
   if(c==NULL) exit(EXIT_FAILURE);
   c->size=0;
   return c;
}


void CATEGORIEinsert(Categorie c, Categoria ca){
   c->categorie[c->size]=ca;
   (c->size)++;
   return;
}


Categoria *CATEGORIEsearch(Categorie c, char *code){
   int i;
   for(i=0; i<c->size; i++)
      if(strcmp(c->categorie[i].codice, code)==0)
         return &c->categorie[i];
   return NULL;
}


void CATEGORIEfree(Categorie c){
   if(c!=NULL)
      free(c);
   return;
}
