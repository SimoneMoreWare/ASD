#ifndef PRODUTTORE_H_INCLUDED
#define PRODUTTORE_H_INCLUDED
#include "modelli.h"

typedef struct prod_s *Produttore;

Produttore PRODUTTOREinit();
Produttore PRODUTTOREread(FILE *f);
void PRODUTTOREprint(Produttore p, FILE *f);
Produttore PRODUTTOREsetNull();
Boolean PRODUTTOREisNull(Produttore p);
void PRODUTTOREaccorpaProduttori(Produttore p1, Produttore p2);
char *PRODUTTOREgetNome(Produttore p);
Modelli PRODUTTOREgetModelli(Produttore p);
void PRODUTTOREfree(Produttore p);

#endif // PRODUTTORE_H_INCLUDED
