#ifndef ARRAY_INCLUDED
#define ARRAY_INCLUDED

#include "sol.h"

typedef struct array *ARRAY;

ARRAY ARRAYinit(int maxN);
void ARRAYpushWithDup(ARRAY sp, SOL s);
SOL ARRAYread(ARRAY sp, int i);
int ARRAYsize(ARRAY sp);
void ARRAYfree(ARRAY sp);

#endif
