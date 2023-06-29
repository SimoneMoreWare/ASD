#ifndef MODELLI_H_INCLUDED
#define MODELLI_H_INCLUDED
#include "modello.h"

typedef struct mods_s *Modelli;

Modelli MODELLIinit();
Modelli MODELLIread(FILE *f);
void MODELLIprint(Modelli m, FILE *f);
void MODELLIcancellaModello(Modelli m, char *modello);
Modello MODELLIcercaModello(Modelli m, char *modello);
int MODELLIsize(Modelli m);
void MODELLIspostaModelli(Modelli m1, Modelli m2);
void MODELLIfree(Modelli m);

#endif // MODELLI_H_INCLUDED
