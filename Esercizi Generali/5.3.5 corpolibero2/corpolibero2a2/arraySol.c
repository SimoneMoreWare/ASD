#ifndef ARRAYSOL_INCLUDED
#define ARRAYSOL_INCLUDED

#include <stdlib.h>
#include "arraySol.h"

struct array {
  SOL *s;
  int M, N;
};


static void growStack(ARRAY sp) { 
  sp->M *= 2;
  sp->s = realloc(sp->s,sp->M*sizeof(SOL));
}

ARRAY ARRAYinit(int maxN) { 
  ARRAY sp = malloc(sizeof *sp) ;
  sp->s = malloc(maxN*sizeof(SOL));
  sp->N=0; sp->M=maxN;
  return sp; 
}

void ARRAYpushWithDup(ARRAY sp, SOL val) { 
  if (sp->N>=sp->M) 
    growStack(sp);
  sp->s[sp->N++] = SOLdup(val);
}

SOL ARRAYread(ARRAY sp, int i) {
  return sp->s[i]; 
}

int ARRAYsize(ARRAY sp) {
  return sp->N; 
}

void ARRAYfree(ARRAY sp) {
  int i;
  for (i=0; i<sp->N; i++) {
    SOLfree(sp->s[i]);
  } 
  free(sp->s);
  free(sp);
}

#endif
