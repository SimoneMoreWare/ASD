#ifndef SCIATORI_H_INCLUDED
#define SCIATORI_H_INCLUDED
#include "sciatore.h"

typedef struct sc_s *Sciatori;

Sciatori SCIATORIinit();
Sciatore *SCIATORIsearch(Sciatori s, long id);
void SCIATORIadd(Sciatori s, Sciatore sc);
void SCIATORIprint(Sciatori s, FILE *f);
void SCIATORIfree(Sciatori s);

#endif // SCIATORI_H_INCLUDED
