#ifndef DIPENDENTI_H_INCLUDED
#define DIPENDENTI_H_INCLUDED
#include "dipendente.h"

typedef struct dip *Dipendenti;

Dipendenti DIPENDENTIinit(int nDipendenti);
Dipendenti DIPENDENTIread(FILE *f);
Dipendente DIPENDENTIgetDipendente(Dipendenti d, int index);
int DIPENDENTIsearch(Dipendenti d, int matricola);
int DIPENDENTIsize(Dipendenti d);
void DIPENDENTIfree(Dipendenti d);

#endif // DIPENDENTI_H_INCLUDED
