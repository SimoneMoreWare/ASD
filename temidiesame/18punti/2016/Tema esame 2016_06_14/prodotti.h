#ifndef PRODOTTI_H_INCLUDED
#define PRODOTTI_H_INCLUDED
#include "prodotto.h"

typedef struct prods *Prodotti;

typedef enum{VERO, FALSO}Boolean;

Prodotti PRODOTTIinit();
void PRODOTTIinsert(Prodotti ps, Prodotto p);
Prodotto *PRODOTTIsearch(Prodotti p, char *code);
Prodotti PRODOTTIsearchByName (Prodotti p, char *name);
void PRODOTTIordinaPerNome(Prodotti p);
void PRODOTTIordinaPerCodice(Prodotti p);
void PRODOTTIprint(Prodotti p, FILE *f);
int PRODOTTIgetSize(Prodotti p);
void PRODOTTIfree(Prodotti p);

#endif // PRODOTTI_H_INCLUDED
