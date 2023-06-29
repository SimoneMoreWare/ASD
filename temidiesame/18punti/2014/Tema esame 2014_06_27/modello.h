#ifndef MODELLO_H_INCLUDED
#define MODELLO_H_INCLUDED
#include "accessori.h"

typedef struct mod_s *Modello;

Modello MODELLOinit();
Modello MODELLOread(FILE *f);
void MODELLOprint(Modello m, FILE *f);
Modello MODELLOsetNull();
Boolean MODELLOisNull(Modello m);
char *MODELLOgetNome(Modello m);
Accessori MODELLOgetAccessori(Modello m);
void MODELLOfree(Modello m);

#endif // MODELLO_H_INCLUDED
