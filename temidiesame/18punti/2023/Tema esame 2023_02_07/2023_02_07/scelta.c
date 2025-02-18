#include "scelta.h"

Scelta SCELTAinit(char *val, int x, int y) {
    Scelta s;

    s = (Scelta) malloc(sizeof(*s));
    s->t = TOKENinit(val);
    s->x = x;
    s->y = y;

    return s;
}

Buffer BUFFERinit(int n, int val) {
    Buffer b;

    b = (Buffer) malloc(sizeof(*b));
    b->n = n;
    b->val = val;
    b->s = (Scelta*) malloc(b->n * sizeof(Scelta));
    
    return b;
}

/*
    Formato:
    N
    HH x y
    [...]
    HH x y
*/
Buffer BUFFERfile(FILE *file) {
    int i, n, x, y;
    char val[TOKEN_DIM];
    Buffer b;

    fscanf(file, "%d", &n);
    b = BUFFERinit(n, 0);
    for (i = 0; i < n; i++) {
        fscanf(file, "%s %d %d", val, &x, &y);
        b->s[i] = SCELTAinit(val, x, y);
    }

    return b;
}

int checkBufferBonus(Buffer *sl, Bonus b) {
    int i, j;

    for (i = 0; i < ((*sl)->n - b->n + 1); i++) {
        if (TOKENcmp((*sl)->s[i]->t, b->t[0]) == 0) {
            for (j = 1; j < b->n; j++)
                if (TOKENcmp((*sl)->s[i+j]->t, b->t[j]) != 0)
                    break;
            if (j == b->n) {
                //printf("%d ", b->val);
                (*sl)->val += b->val;
                break;
            }
        }
    }

    return 0;
}

int checkGridBuffer(Grid grid, Buffer *sl, BonusList bl) {
    int i, isPari;
    Token t;

    if ((*sl)->s[0]->x != 0)
        return 0;

    if (TOKENcmp((*sl)->s[0]->t, grid->m[(*sl)->s[0]->x][(*sl)->s[0]->y]) != 0)
        return 0;

    for (i = 1; i < (*sl)->n; i++) {
        isPari = (i%2 == 0);

        if (isPari && (*sl)->s[i]->x != (*sl)->s[i-1]->x)
            return 0;

        if (!isPari && (*sl)->s[i]->y != (*sl)->s[i-1]->y)
            return 0;
        
        t = grid->m[(*sl)->s[i]->x][(*sl)->s[i]->y];
        if (TOKENcmp(t, (*sl)->s[i]->t) != 0)
            return 0;
    }

    for (i = 0; i < bl->n; i++) {
        checkBufferBonus(sl, bl->b[i]);
    }

    return 1;
} 

Buffer BUFFERcopy(Buffer copy) {
    int i;
    Buffer b;

    b = BUFFERinit(copy->n, copy->val);
    for (i = 0; i < b->n; i++)
       b->s[i] = SCELTAinit(copy->s[i]->t->val, copy->s[i]->x, copy->s[i]->y);

    return b;
}

void BUFFERprint(Buffer b) {
    int i;

    printf("N = %d\n", b->n);
    printf("VAL = %d\n", b->val);
    printf("MOSSE = ");
    for (i = 0; i < b->n; i++)
        printf("%s ", b->s[i]->t->val);
    printf("\n");
}