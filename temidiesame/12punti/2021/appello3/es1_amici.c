#include <stdio.h>

#define N 6

int M[N][N] = {{0, 1, 1, 0, 0, 0},
               {1, 0, 0, 1, 1, 1},
               {1, 0, 0, 0, 1, 0},
               {0, 1, 0, 0, 1, 1},
               {0, 1, 1, 1, 0, 1},
               {0, 1, 0, 1, 1, 0}};

void coppieKAmici(int mat[N][N], int k) {
    int i, j, count;
    for (i = 0; i < N; i++) {
        for (j = i + 1; j < N; j++) {
            count = 0;
            for (int p = 0; p < N; p++) {
                if (mat[i][p] == 1 && mat[j][p] == 1)
                    count++;
            }
            if (count == k)
                printf("(%d, %d)\n", i, j);
        }
    }
}

int main() {
    coppieKAmici(M, 2);
    return 0;
}
