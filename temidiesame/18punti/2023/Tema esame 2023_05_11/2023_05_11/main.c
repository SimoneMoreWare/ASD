#include "Graph.h"

int main() {
    FILE *file;
    char grafo[30], test[30];
    Graph G;
    int i, n, exp;

    printf("Nome File (grafo): ");
    scanf("%s", grafo);

    file = fopen(grafo, "r");
    G = GRAPHfile(file);

    GRAPHfindMaxTripack(G);
    fclose(file);
    printf("\n");

    printf("Nome File (test): ");
    scanf("%s", test);

    file = fopen(test, "r");
    fscanf(file, "%d", &n);
    for(i = 0; i < n; i++) {
        printf("TEST #%d\n", i+1);
        fscanf(file, "%d", &exp);
        printf("EXPECTED = %d\n", exp);
        printf("OBTAINED = %d\n\n", GRAPHcheckFile(file, G));
    }
    return 0;
}