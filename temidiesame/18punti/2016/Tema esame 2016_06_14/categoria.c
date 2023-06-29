#include "categoria.h"

Categoria CATEGORIAcrea(char *code){
   Categoria c;
   strcpy(c.codice, code);
   c.p=PRODOTTIinit();
   return c;
}


Prodotto *CATEGORIAsearchProdotto(Categoria c, char *codice){
   return PRODOTTIsearch(c.p, codice);
}


void CATEGORIAstampaProdotti(Categoria c, char *ordinamento, FILE *f){
   if(PRODOTTIgetSize(c.p)==0){
      printf("La categoria %s non contiene alcun prodotto.\n", c.codice);
      return;
   }
   if(strcmp(ordinamento, "nome")==0)
      PRODOTTIordinaPerNome(c.p);
   PRODOTTIprint(c.p, f);
   if(strcmp(ordinamento, "nome")==0)
      PRODOTTIordinaPerCodice(c.p);
   return;
}


void CATEGORIAinsertProdotto(Categoria *c, Prodotto p){
    PRODOTTIinsert(c->p, p);
    return;
}
