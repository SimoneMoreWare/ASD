#ifndef PAROLE_H_INCLUDED
#define PAROLE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "wordLun.h"

typedef struct{
	WordLun parole[MAX];
}Parole;

Parole PAROLEcrea();
Parole PAROLEread(FILE *f);
void PAROLEclear(Parole p);



#endif // PAROLE_H_INCLUDED
