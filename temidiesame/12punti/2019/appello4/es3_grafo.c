#include <stdio.h>

typedef struct { int v; int w; int wt;} Edge;

int find(int parent[], int i) {
  if (parent[i] == i) return i;
  return parent[i] = find(parent, parent[i]);
}

int C_MST(int nV, int nE, Edge *edges) {
  int i, j, wt = 0;
  int parent[nV];

  // Inizializzazione del vettore parent
  for (i = 0; i < nV; i++) parent[i] = i;

  // Ordinamento degli archi in ordine crescente di peso
  for (i = 0; i < nE - 1; i++) {
    for (j = i + 1; j < nE; j++) {
      if (edges[i].wt > edges[j].wt) {
        Edge temp = edges[i];
        edges[i] = edges[j];
        edges[j] = temp;
      }
    }
  }

  for (i = 0; i < nE; i++) {
    int x = find(parent, edges[i].v);
    int y = find(parent, edges[i].w);

    if (x != y) {
      wt += edges[i].wt;
      parent[x] = y;
    }
  }

  return wt;
}

int C_isSpanningTree(int nV, int nE, Edge *edges) {
  int i;
  int parent[nV];
  int count = 0;

  // Inizializzazione del vettore parent
  for (i = 0; i < nV; i++) parent[i] = i;

  for (i = 0; i < nE; i++) {
    int x = find(parent, edges[i].v);
    int y = find(parent, edges[i].w);

    if (x != y) {
      parent[x] = y;
      count++;
    }
  }

  return count == nV - 1;
}

int main() {
  int nV = 4, nE = 5;
  Edge edges[] = {{0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4}};

  int weight = C_MST(nV, nE, edges);
  printf("Peso dell'albero ricoprente minimo: %d\n", weight);

  int isSpanningTree = C_isSpanningTree(nV, nE, edges);
  printf("L'insieme di archi rappresenta un albero ricoprente: %s\n", (isSpanningTree ? "si" : "no"));

  return 0;
}
