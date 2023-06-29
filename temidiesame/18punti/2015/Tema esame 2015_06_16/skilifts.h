#ifndef SKILITS_H_INCLUDED
#define SKILITS_H_INCLUDED
#include "skilift.h"

typedef struct sk_s *Skilifts;

Skilifts SKILIFTSinit();
Skilifts SKILIFTSread(FILE *f);
Skilift *SKILIFTSsearch(Skilifts s, char *id);
void SKILIFTSadd(Skilifts s, Skilift sk);
void SKILIFTSprint(Skilifts s, FILE *f);
void SKILIFTSfree(Skilifts s);

#endif // SKILITS_H_INCLUDED
