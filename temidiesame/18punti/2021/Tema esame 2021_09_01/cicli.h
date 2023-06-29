#ifndef CICLI_H_INCLUDED
#define CICLI_H_INCLUDED
#include "ciclo.h"

typedef struct cicli *Cicli;

Cicli CICLIinit();
void CICLIinsert(Cicli c, Ciclo ci);
Ciclo CICLIgetCiclo(Cicli c, int index);
int CICLIgetNumCicli(Cicli c);
Cicli CICLIread(FILE *f);
void CICLIfree(Cicli c);



#endif // CICLI_H_INCLUDED
