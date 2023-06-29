#ifndef PRODUTTORI_H_INCLUDED
#define PRODUTTORI_H_INCLUDED
#include "produttore.h"

typedef struct prods_s *Produttori;

Produttori PRODUTTORIinit();
Produttori PRODUTTORIread(FILE *f);
void PRODUTTORIprint(Produttori p, FILE *f);
Produttore PRODUTTORIcercaProduttore(Produttori p, char *produttore);
void PRODUTTORIeliminaProduttore(Produttori p, char *produttore);
int PRODUTTORIsize(Produttori p);
void PRODUTTORIcompattaProduttori(Produttori p, char *prod1, char *prod2);
void PRODUTTORIfree(Produttori p);

#endif // PRODUTTORI_H_INCLUDED
