#ifndef SCHEMA_H_INCLUDED
#define SCHEMA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct{
       int **mat;
       int nr, nc;
}Schema;

Schema SCHEMAread(FILE *f);
void SCHEMAprint(Schema s, FILE *f);
void SCHEMAclear(Schema s);

#endif // SCHEMA_H_INCLUDED
