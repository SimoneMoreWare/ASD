#ifndef DIVISIONI_H_INCLUDED
#define DIVISIONI_H_INCLUDED
#include "divisione.h"

typedef struct divs *Divisioni;

Divisioni DIVISIONIinit(int nDiv);
Divisioni DIVISIONIread(FILE *f);
Divisione DIVISIONIgetDivisione(Divisioni d, int index);
int DIVISIONIsearch(Divisioni d, char *sigla);
float DIVISIONIscostamentoMedio(Divisioni d, int **compTot);
Boolean DIVISIONIcheck(Divisioni d, int **compTot, int **addTot);
int DIVISIONIsize(Divisioni d);
void DIVISIONIprintAssociazioni(Divisioni d, FILE *f);
void DIVISIONIfree(Divisioni d);


#endif // DIVISIONI_H_INCLUDED
