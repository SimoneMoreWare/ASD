#ifndef PIATTI_H_INCLUDED
#define PIATTI_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "piatto.h"

typedef struct piatti_s *Piatti;

Piatti PIATTIinit(int dim);
Piatti PIATTIread(FILE *f);
void PIATTIprint(Piatti p, FILE *f);
Piatto PIATTIgetPiatto(Piatti p, int index);
int PIATTIsize(Piatti p);
void PIATTIfree(Piatti p);

#endif // PIATTI_H_INCLUDED
