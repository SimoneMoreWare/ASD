#ifndef BONUS_H
#define BONUS_H
#include "token.h"

typedef struct bonus_t {
    int n, val;
    Token *t;
} *Bonus;

Bonus BONUSinit(int n, int val);
Bonus BONUSfile(FILE* file);
int BONUScmp(Bonus b1, Bonus b2);
int BONUSgetVal(Bonus b);

#endif