#include <stdio.h>
#include "stdlib.h"

void powerset(int *length, int *prices, int *sol, int pos, int m, int n, int *best, int *best_value);

int main() {
    int m = 8;
    int n = 6;
    int lunghezza[8] = {7, 4, 8, 1, 5, 2, 6, 3};
    int prezzo[8] = {17, 9, 20, 1, 10, 5, 17, 8};
    int *sol = calloc(6, sizeof(int));
    int best[6] = {0, 0, 0, 0, 0, 0};
    int best_value = 0;
    powerset(lunghezza, prezzo, sol, 0, m, n, best, &best_value);
    printf("%d\n", best_value);
    printf("Nastro tagliato in posizione: ");
    for (int i = 0; i < n; i++) {
        if (best[i] != 0)
            printf("%d ", i);
    }
    return 0;
}

void powerset(int *length, int *prices, int *sol, int pos, int m, int n, int *best, int *best_value) {
    int i = 0, j, k, value = 0;
    if (pos >= n) {
        for (j = 0; j < n; j++)
            if (sol[j] == 1) {
                for (k = 0; k < m; k++)
                    if (length[k] == i + 1) {
                        value += prices[k];
                        i = 0;
                    }
            } else
                i++;
        if (value > *best_value) {
            *best_value = value;
            for (j = 0; j < n; j++)
                best[j] = sol[j];
        }
    }
    for (j = 0; j < m; j++) {
        if (length[j] == pos + 1) {
            sol[pos] = 1;
            powerset(length, prices, sol, pos + 1, m, n, best, best_value);
            sol[pos] = 0;
            powerset(length, prices, sol, pos + 1, m, n, best, best_value);
            break;
        }
    }
}