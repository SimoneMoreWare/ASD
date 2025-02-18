#include "grid.h"

Grid GRIDinit(int N) {
    int i;
    Grid g;

    g = (Grid) malloc(sizeof(*g));
    g->N = N;
    g->m = (Token**) malloc(g->N * sizeof(Token*));
    for (i = 0; i < g->N; i++) {
        g->m[i] = (Token*) malloc(g->N * sizeof(Token));
    }

    return g;
}

Grid GRIDfile(FILE* file) {
    int i, j, n;
    char tmp[TOKEN_DIM];
    Grid g;

    fscanf(file, "%d", &n);
    g = GRIDinit(n);
    for (i = 0; i < g->N; i++)
        for (j = 0; j < g->N; j++) {
            fscanf(file, "%s", tmp);
            g->m[i][j] = TOKENinit(tmp);
        }

    return g;
}


