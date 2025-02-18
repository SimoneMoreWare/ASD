#ifndef GRID_H
#define GRID_H
#include "bonusList.h"

typedef struct grid_t {
    int N;
    Token **m;
} *Grid;

typedef enum direction_t {
    column,
    row
} Direction;

Grid GRIDinit(int N);
Grid GRIDfile(FILE* file);

#endif