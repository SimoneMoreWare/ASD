#ifndef CATEGORIA_H_INCLUDED
#define CATEGORIA_H_INCLUDED
#include "prodotti.h"

typedef struct{
   char codice[MAXC];
   Prodotti p;
}Categoria;

Categoria CATEGORIAcrea(char *code);
Prodotto *CATEGORIAsearchProdotto(Categoria c, char *codice);
void CATEGORIAstampaProdotti(Categoria c, char *ordinamento, FILE *f);
void CATEGORIAinsertProdotto(Categoria *c, Prodotto p);

#endif // CATEGORIA_H_INCLUDED
