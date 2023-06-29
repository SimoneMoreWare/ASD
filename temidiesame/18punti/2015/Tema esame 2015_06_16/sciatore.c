#include "sciatore.h"

Sciatore SCIATOREcrea(long cardId){
   Sciatore s;
   s.cardId=cardId;
   s.passaggi=AUTORIZZAZIONISinit();
   return s;
}


Sciatore SCIATOREsetNull(){
    Sciatore s;
    s.cardId=-1;
    s.nVolte=-1;
    return s;
}


void SCIATOREaddPassaggio(Sciatore *s, AutorizzazioneS as){
    AUTORIZZAZIONISadd(s->passaggi, as);
    return;
}


AutorizzazioneS *SCIATOREcercaPassaggioSciatore(Sciatore s, char *skilift){
    return AUTORIZZAZIONISsearch(s.passaggi, skilift);
}


void SCIATOREprint(Sciatore s, FILE *f){
    fprintf(f, "Sciatore %ld:\n", s.cardId);
    fprintf(f, "\t---PASSAGGI---\n");
    AUTORIZZAZIONISprint(s.passaggi, f);
    return;
}


void SCIATOREclear(Sciatore s){
    AUTORIZZAZIONISfree(s.passaggi);
    return;
}
