#ifndef AUTORIZZAZIONISKILIFT_H_INCLUDED
#define AUTORIZZAZIONISKILIFT_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

//AUTORIZZAZIONE SKILIFT
typedef struct{
    long sciatore;
    int nVolte;
}AutorizzazioneSk;

AutorizzazioneSk AUTORIZZAZIONESKcrea(long sciatore);
AutorizzazioneSk AUTORIZZAZIONESKsetNull();
void AUTORIZZAZIONESKincrementaNumVolte(AutorizzazioneSk *as);
void AUTORIZZAZIONESKprint(AutorizzazioneSk as, FILE *f);


//AUTORIZZAZIONI SKILIFT
typedef struct ask_s *AutorizzazioniSk;

AutorizzazioniSk AUTORIZZAZIONISKinit();
AutorizzazioneSk *AUTORIZZAZIONISKsearch(AutorizzazioniSk as, long sciatore);
void AUTORIZZAZIONISKadd(AutorizzazioniSk as, AutorizzazioneSk a);
int AUTORIZZAZIONISKsize(AutorizzazioniSk as);
void AUTORIZZAZIONISKprint(AutorizzazioniSk as, FILE *f);
void AUTORIZZAZIONISKfree(AutorizzazioniSk as);

#endif // AUTORIZZAZIONISKILIFT_H_INCLUDED
