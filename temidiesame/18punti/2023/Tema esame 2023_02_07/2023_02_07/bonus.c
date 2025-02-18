#include "bonus.h"

Bonus BONUSinit(int n, int val) {
    Bonus b;

    b = (Bonus) malloc(sizeof(*b));
    b->n = n;
    b->val = val;
    b->t = (Token*) malloc(n*sizeof(Token));

    return b;
}

Bonus BONUSfile(FILE* file) {
    int i, n, val;
    char tmp[TOKEN_DIM];
    Bonus b;

    fscanf(file, "%d %d", &n, &val);
    b = BONUSinit(n, val);
    for (i = 0; i < n; i++) {
        fscanf(file, "%s", tmp);
        b->t[i] = TOKENinit(tmp);
    }

    return b;
}

int BONUScmp(Bonus b1, Bonus b2) {
    int i;

    if (b1->n != b2->n)
        return 0;
    
    if (b1->val != b2->val)
        return 0;
    
    for (i = 0; i < b1->n; i++)
        if (TOKENcmp(b1->t[i], b2->t[i]) != 0)
            return 0;
    
    return 1;
}

int BONUSgetVal(Bonus b) {
    return b->val;
}