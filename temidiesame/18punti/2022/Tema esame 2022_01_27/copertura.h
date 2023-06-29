#ifndef COPERTURA_H_INCLUDED
#define COPERTURA_H_INCLUDED
#include "griglia.h"

typedef struct{
    int riga, colonna, base, altezza;
}Regione;

typedef struct{
    Regione *regioni;
    int dim, maxD;
}Copertura;

//REGIONE
Regione REGIONEcrea(int riga, int colonna, int base, int altezza);
Regione REGIONEsetNull();
Regione REGIONEread(FILE *f);
Boolean REGIONEisNull(Regione r);
void REGIONEprint(Regione r, FILE *f);


//COPERTURA
Copertura COPERTURAinit(int maxD);
Copertura COPERTURAread(FILE *f);
void COPERTURAinsert(Copertura *c, Regione r);
void COPERTURAdelete(Copertura *c);
Boolean COPERTURAcheck(Copertura c, Griglia g, int *nRegioni, int areaBianco);
void COPERTURAsolve(Griglia g);
void COPERTURAprint(Copertura c, FILE *f);
void COPERTURAclear(Copertura c);

#endif // COPERTURA_H_INCLUDED
