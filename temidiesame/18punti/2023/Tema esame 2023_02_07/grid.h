#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED
#include "token.h"

typedef struct{
   Token **grid;
   int nr, nc;
}Grid;

Grid GRIDread(FILE *f);
void GRIDclear(Grid *g);

#endif // GRID_H_INCLUDED
