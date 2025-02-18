#ifndef SCELTA_H
#define SCELTA_H
#include "grid.h"

typedef struct scelta_t {
    Token t;
    int x, y;
} *Scelta;

typedef struct buffer_t {
    int n, val;
    Scelta *s;
} *Buffer;

Scelta SCELTAinit(char *val, int x, int y);
Buffer BUFFERinit(int n, int val);
Buffer BUFFERfile(FILE *file);
Buffer BUFFERcopy(Buffer copy);
void BUFFERprint(Buffer b);
int checkBufferBonus(Buffer *sl, Bonus b);
int checkGridBuffer(Grid grid, Buffer *sl, BonusList bl);


#endif