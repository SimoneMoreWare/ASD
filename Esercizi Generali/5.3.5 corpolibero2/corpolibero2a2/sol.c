#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "sol.h"

struct sol_s {
  int *solV;
  int maxN;
  int n;
  float diff;
  float punti;
};

SOL SOLnew(int maxN) {
  SOL s;
  s = malloc(sizeof(struct sol_s));
  s->solV = malloc(maxN*sizeof(int));
  s->maxN = maxN;
  s->n = 0;
  s->diff = s->punti = 0.0;
  return s;
}

void SOLcopy(SOL sDest, SOL sSrc) {
  int i;
  if (sDest->maxN<sSrc->n) {
    /* non abbastanza, rialloca */
    sDest->maxN = sSrc->n;
    sDest->solV = realloc(sDest->solV,sDest->maxN*sizeof(int));
  }
  sDest->n = sSrc->n;
  sDest->diff = sSrc->diff;
  sDest->punti = sSrc->punti;
  for (i=0; i<sDest->n; i++) {
    sDest->solV[i] = sSrc->solV[i];
  }
}

SOL SOLdup(SOL s) {
  int i;
  SOL s2 = SOLnew(s->n);
  SOLcopy(s2,s);
  return s2;
}
void SOLfree(SOL s) {
  free(s->solV);
  free(s);
}

int SOLreadI(SOL s, int i) {
  assert(i>=0 && i<s->n);
  return (s->solV[i]);
}

void SOLwriteI(SOL s, int i, int val) {
  assert(i>=0 && i<s->n);
  s->solV[i] = val;
}

void SOLread(SOL s, float *dp, float *pp) {
  if (dp!=NULL) *dp = s->diff;
  if (pp!=NULL) *pp = s->punti;
}

void SOLwrite(SOL s, float d, float p) {
  s->diff = d;
  s->punti = p;
}

int SOLreadN(SOL s) {
  return s->n;
}

void SOLwriteN(SOL s, int n) {
  s->n = n;
}

float SOLreadD(SOL s) {
  return s->diff;
}

void SOLwriteD(SOL s, float d) {
  s->diff = d;
}

float SOLreadP(SOL s) {
  return s->punti;
}

void SOLwriteP(SOL s, float p) {
  s->punti = p;
}

