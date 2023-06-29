#ifndef SCHEMA_H_INCLUDED
#define SCHEMA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "posizione.h"

typedef struct{
	int dim;
	int nr, nc;
    Posizione *posizioni;
}Schema;

Schema SCHEMAread(FILE *f);
void SCHEMAclear(Schema s);


#endif // SCHEMA_H_INCLUDED
