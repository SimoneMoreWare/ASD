#ifndef ACCESSORI_H_INCLUDED
#define ACCESSORI_H_INCLUDED
#include "accessorio.h"

typedef struct accs *Accessori;

Accessori ACCESSORIinit();
Accessori ACCESSORIread(FILE *f);
void ACCESSORIprint(Accessori a, FILE *f);
void ACCESSORIcancellaAccessorio(Accessori a, char *nomeAccessorio);
Accessorio ACCESSORIcercaAccessorio(Accessori a, char *nome);
int ACCESSORIsize(Accessori a);
void ACCESSORIfree(Accessori a);

#endif // ACCESSORI_H_INCLUDED
