#ifndef AUTORIZZAZIONISCIATORE_H_INCLUDED
#define AUTORIZZAZIONISCIATORE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define MAX 11

//AUTORIZZAZIONE SCIATORE
typedef struct{
    char skilift[MAX];
    char time[6];
}AutorizzazioneS;

AutorizzazioneS AUTORIZZAZIONEScrea(char *skilift, char *time);
void AUTORIZZAZIONESsetOra(AutorizzazioneS *as, char *time);
AutorizzazioneS AUTORIZZAZIONESsetNull();
void AUTORIZZAZIONESprint(AutorizzazioneS as, FILE *f);

//AUTORIZZAZIONI SCIATORE
typedef struct as_s *AutorizzazioniS;

AutorizzazioniS AUTORIZZAZIONISinit();
AutorizzazioneS *AUTORIZZAZIONISsearch(AutorizzazioniS as, char *skilift);
void AUTORIZZAZIONISadd(AutorizzazioniS as, AutorizzazioneS a);
int AUTORIZZAZIONISsize(AutorizzazioniS as);
void AUTORIZZAZIONISprint(AutorizzazioniS as, FILE *f);
void AUTORIZZAZIONISfree(AutorizzazioniS as);

#endif // AUTORIZZAZIONISCIATORE_H_INCLUDED
