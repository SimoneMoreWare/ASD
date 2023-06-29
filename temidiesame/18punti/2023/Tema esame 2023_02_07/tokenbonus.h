#ifndef TOKENBONUS_H_INCLUDED
#define TOKENBONUS_H_INCLUDED
#include "token.h"

typedef struct{
   Token *t;
   int bonus, dim;
}TokenBonus;

TokenBonus TOKENBONUSread(FILE *f);
void TOKENBONUSclear(TokenBonus *tb);

#endif // TOKENBONUS_H_INCLUDED
