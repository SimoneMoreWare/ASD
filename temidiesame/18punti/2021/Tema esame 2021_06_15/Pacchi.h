#ifndef PACCHI_H_INCLUDED
#define PACCHI_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "Pacco.h"

typedef struct pacchi_s *Pacchi;

Pacchi PACCHIinit();
Pacchi PACCHIread(FILE *f);
Pacco *PACCHIsearchPacco(Pacchi p, char *code);
void PACCHIprintCode(Pacchi p, FILE  *f);
void PACCHIfree(Pacchi p);

#endif // PACCHI_H_INCLUDED
