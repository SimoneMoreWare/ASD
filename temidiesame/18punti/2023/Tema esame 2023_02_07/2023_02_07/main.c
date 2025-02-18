#include "scelta.h"

void checkMosse(Grid grid, char *filenameBonus, char *filenameBuffer) {
    Buffer b;
    BonusList bl;
    FILE *file;

    file = fopen(filenameBonus, "r");
    bl = BONUSLISTfile(file);
    fclose(file);

    file = fopen(filenameBuffer, "r");
    b = BUFFERfile(file);
    fclose(file);

    checkGridBuffer(grid, &b, bl);
    printf("File Bonus = %s\n", filenameBonus);
    printf("File Buffer = %s\n", filenameBuffer);
    BUFFERprint(b);
    printf("\n");
}

void findSol(int pos, Grid grid, Buffer *best_sol, Buffer sol, BonusList bl) {
    int i, isPari;
    Scelta prev;

    if (pos >= sol->n) {
        sol->val = 0;
        checkGridBuffer(grid, &sol, bl);
        if (sol->val > (*best_sol)->val) {
            *best_sol = BUFFERcopy(sol);
        }
        return;
    }

    for (i = 0; i < grid->N; i++) {
        isPari = (pos%2 == 0);

        if (pos == 0) {
            sol->s[pos] = SCELTAinit(grid->m[i][0]->val, i, 0);
        }

        if (pos > 0) {
            prev = sol->s[pos-1];
            if (!isPari) {
                sol->s[pos] = SCELTAinit(grid->m[i][prev->y]->val, i, prev->y);
            } else {
                sol->s[pos] = SCELTAinit(grid->m[prev->x][i]->val, prev->x, i);
            }
        }
        
        findSol(pos+1, grid, best_sol, sol, bl);
    }
}

int main() {
    int L;
    FILE *file;
    Grid grid;
    BonusList bl;
    Buffer best_sol, sol;

    file = fopen("grid.txt", "r");
    grid = GRIDfile(file);
    fclose(file);

    printf("--------- TESTS ---------\n");
    checkMosse(grid, "bonus1.txt", "mosse.txt");
    checkMosse(grid, "bonus2.txt", "mosse1.txt");
    checkMosse(grid, "bonus2.txt", "mosse2.txt");

    printf("------- SOLUZIONE -------\n");
    printf("L = ");
    scanf("%d", &L);
    best_sol = BUFFERinit(L, 0);
    sol = BUFFERinit(L, 0);
    file = fopen("bonus2.txt", "r");
    bl = BONUSLISTfile(file);
    findSol(0, grid, &best_sol, sol, bl);
    BUFFERprint(best_sol);

    return 0;
}