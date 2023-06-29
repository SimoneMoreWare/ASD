#include "citta.h"

Citta CITTAread(FILE *f){
   Citta c;
   fscanf(f, "%s %d %d", c.nome, &c.abitanti, &c.distanzaInizio);
   return c;
}


void CITTAprint(Citta c, FILE *f){
    fprintf(f, "%s %d %d\n", c.nome, c.abitanti, c.distanzaInizio);
    return;
}


Simboli CITTAcompare(Citta c1, Citta c2){
    if(strcmp(c1.nome, c2.nome)==0 && c1.abitanti==c2.abitanti && c1.distanzaInizio==c2.distanzaInizio)
      return UGUALE;
    return DIVERSO;
}
