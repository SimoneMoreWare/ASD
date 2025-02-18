#include "bonusList.h"

BonusList BONUSLISTinit(int n) {
    int i;
    BonusList bl;

    bl = (BonusList) malloc(sizeof(*bl));
    bl->n = n;
    bl->b = (Bonus*) malloc(n*sizeof(Bonus));
    for (i = 0; i < bl->n; i++)
        bl->b[i] = BONUSinit(0, 0);

    return bl;
}

BonusList BONUSLISTfile(FILE* file) {
    int i, n_b;
    BonusList bl;

    fscanf(file, "%d", &n_b);
    bl = BONUSLISTinit(n_b);
    for (i = 0; i < n_b; i++) {
        bl->b[i] = BONUSfile(file);
    }

    return bl;
}