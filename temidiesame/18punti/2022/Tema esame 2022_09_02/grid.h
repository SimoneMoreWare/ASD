#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char **griglia;
    int nr, nc;
}Grid;

Grid GRIDcrea(int nr, int nc);
Grid GRIDread(FILE *f);
void GRIDclear(Grid g);
void GRIDprint(Grid g, FILE *f);

#endif // GRID_H_INCLUDED
