#ifndef BONUSLIST_H
#define BONUSLIST_H
#include "bonus.h"

typedef struct bonusList_t {
    int n;
    Bonus *b;
} *BonusList;

BonusList BONUSLISTinit(int n);
BonusList BONUSLISTfile(FILE* file);

#endif