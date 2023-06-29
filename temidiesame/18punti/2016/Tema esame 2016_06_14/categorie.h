#ifndef CATEGORIE_H_INCLUDED
#define CATEGORIE_H_INCLUDED
#include "categoria.h"

typedef struct cats *Categorie;

Categorie CATEGORIEinit();
void CATEGORIEinsert(Categorie c, Categoria ca);
Categoria *CATEGORIEsearch(Categorie c, char *code);
void CATEGORIEfree(Categorie c);

#endif // CATEGORIE_H_INCLUDED
