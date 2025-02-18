/*
 * Analisi del problema
 *
 * Ogni tupla che identifica un vertex cover può essere
 * riportato ad un caso di combinazione semplice, dove gli
 * n oggetti sono i vertici del grafo, e dove k è la
 * dimensione della tupla presa in considerazione.
 * 
 * In caso il grafo fosse connesso, la quantità di
 * vertex cover risulterebbe:
 *  C(n,k) = sum(C(n,k)), con 1 <= k <= n
 * 
 * In questo esercizio, viene esplicitato che il grafo non è
 * connesso, perciò la quantità di vertex cover dipende da 
 * dove compaiono essi stessi nei rami:
 * - se un vertice compare in tutti i rami, in qualsiasi
 *   tupla esso sia, quella tupla risulterà vertex cover;
 * - se un vertice compare in alcuni rami, potrà potenzialmente 
 *   risultare vertex cover solo in tuple di dimensione
 *   maggiore di 1.
 * 
 * Si esegue l'algoritmo di combinazione per determinare
 * tutti i vertex cover possibili con la quantità di 
 * vertici disponibili. Nel caso in cui una tupla risulti 
 * soluzione, si esegue la ricorsione, altrimenti si termina
 * il ramo dell'albero legato a quella tupla.
 */
#include <stdio.h>
#include <stdlib.h>
#define nomeFile "grafo.txt"

void print_tuple(int* tuple, int n) {
    int i;
    printf("{");
    for(i = 0; i < n; i++) {
        printf("%d", tuple[i]);
        if(i != n-1) {
            printf(",");
        }
    }
    printf("}");
}

int acceptable(int* N, int** E, int n, int n_E) {
    int* connected_arches = (int*)calloc(n_E, sizeof(int));
    int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < n_E; j++)
            if(N[i] == E[j][0] || N[i] == E[j][1])
                connected_arches[j] = 1;

    for(j = 0; j < n_E; j++)
        if(connected_arches[j] == 0) {
            free(connected_arches);
            return 0;
        }
    free(connected_arches);
    return 1;
}

int combine(int pos, int* N, int* sol, int** E, int n_N, int k, int n_E, int start, int cnt) {
    int i;
    if (pos >= k) {
        if(acceptable(sol, E, k, n_E)) {
            print_tuple(sol, k);
            printf(" ");
            return cnt+1;
        }
    }
    for(i = start; i < n_N; i++) {
        sol[pos] = N[i];
        cnt = combine(pos+1, N, sol, E, n_N, k, n_E, i+1, cnt);
    }
    return cnt;
}

int find_vertex_covers(int* N, int** E, int n_N, int n_E) {
    int k, cnt = 0;
    for(k = 1; k < n_N+1; k++) {
        int* sol = (int*) malloc(k*sizeof(int));
        cnt = combine(0, N, sol, E, n_N, k, n_E, 0, cnt);
        free(sol);
    }
    return cnt;
}

int main() {
    FILE* f;
    if((f = fopen(nomeFile, "r")) == NULL) {
        printf("Non è stato possibile aprire il file.");
        return 0;
    }

    int n_N, n_E;
    fscanf(f, "%d", &n_N);
    fscanf(f, "%d", &n_E);
    
    int* N = (int*) malloc(n_N*sizeof(int));
    int** E = (int**) malloc(n_E*sizeof(int*));

    int i;
    for(i = 0; i < n_N; i++) {
        N[i] = i;
    }
    for(i = 0; i < n_E; i++) {
        E[i] = (int*) malloc(2*sizeof(int));
        fscanf(f, "%d", &E[i][0]);
        fscanf(f, "%d", &E[i][1]);
    }
    fclose(f);

    int n_sol = find_vertex_covers(N, E, n_N, n_E);

    printf("\nSono presenti %d vertex covers.", n_sol);

    return 0;
}