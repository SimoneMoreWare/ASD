#ifndef BONUS_H_INCLUDED
#define BONUS_H_INCLUDED
#include "tokenbonus.h"

typedef struct{
   TokenBonus *tbonus;
   int dim;
}Bonus;

Bonus BONUSread(FILE *f);
void BONUSclear(Bonus *b);


#endif // BONUS_H_INCLUDED
