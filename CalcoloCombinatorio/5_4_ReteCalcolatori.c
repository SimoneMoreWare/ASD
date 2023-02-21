#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ts.h"
#include "Queue.h"

#define MAX_LEN 20+1
#define P_INF 1e7 // valore +infinito

TS elencoNodi;
int *best_sol = NULL;
int best_sol_num = -1;

int leggiNodi(char *filename) {
  FILE *fp = fopen(filename, "r");
  char nomeNodo[MAX_LEN];
  elencoNodi = TScrea(1);
  while(fscanf(fp,"%s", nomeNodo) == 1) TSaggiungi(elencoNodi, nomeNodo);
  fclose(fp);
  return TSdimensione(elencoNodi);
}

int **initMat(int dim, int val) {
  int i, j, **m = (int**) malloc(dim * sizeof(int*));
  for (i = 0; i < dim; i++) 
    m[i] = (int*) malloc(dim * sizeof(int));
  for (i = 0; i < dim; i++)
    for (j = 0;j < dim; j++) 
      m[i][j] = val;
  return m;
}

void freeMatrix(int dim, int **m) {
  int i;
  if (m == NULL) 
    return;
  for (i = 0; i < dim; i++) 
    if (m[i] != NULL) 
      free(m[i]);
  free(m);
}

int check_sol(int **adjMat, int nV, int p, int m, int flag_stampa) {

  int i, j;
  // Test grado <= m
  for (i=0;i<nV;i++) {
    int grado = 0;
    for (j = 0; j < nV; j++) 
      if(adjMat[i][j]) 
        grado++;
    if (grado > m) {
      if (flag_stampa) printf("Vincolo sul grado violato\n");
      return -1;
    }
  }

  // Test distanza <= p
  // Matrice di distanza tra tutti i nodi
  int **dist = initMat(nV, P_INF);
  // Strutture dati per BFS
  int *visited = malloc(nV * sizeof(int));
  Q q = QUEUEinit();
  int next_index = -1;

  // Ogni nodo dista 0 da se stesso
  for (i = 0; i < nV; i++) 
    dist[i][i] = 0;

  // Esegui una BFS per nodo, usandolo come radice
  for (i = 0; i < nV; i++) {
    for (j = 0; j < nV; j++) 
      visited[j] = 0;
    QUEUEput(q, i);
    visited[i] = 1;
    while (!QUEUEempty(q)) {
      next_index = QUEUEget(q);
      for (j = 0;j < nV; j++) {
        if (adjMat[next_index][j] && !visited[j]) {
          visited[j] = 1;
          QUEUEput(q, j);
          // aggiorna distanza del j-esimo dono dalla sorgente
          dist[i][j] = dist[i][next_index]+1; 
        }
      }
    }
  }

  // Se il cammino piu' corto tra (i,j) supera p, nessun altro cammino 
  // puo' soddisfare il vincolo. Se la distanza e' rimasta a P_INF, manca
  // del tutto la connettività
  for (i = 0; i < nV; i++) {
    for (j = 0; j < nV; j++) {
      if(dist[i][j] > p) {
        if (flag_stampa) 
          printf("Vincolo sulla lunghezza violato\n");
        freeMatrix(nV, dist);
        free(visited);
        QUEUEfree(q);
        return 1;
      }
    }
  }
  freeMatrix(nV, dist);
  free(visited);
  QUEUEfree(q);
  return 0;
}

void trovaArchi_r(int nV, int p, int m, int pos, 
                  int *elencoArchi, int maxArchiDistinti) {
  if (pos == maxArchiDistinti) { 
    int i, j, k = 0, archiUsati = 0;
    int **adjMat = initMat(nV, 0);
    // Genera matrice di adiacenza dagli archi scelti
    for (i = 0; i < nV-1; i++) {
      for (j = i+1; j < nV; j++) {
        if (elencoArchi[k++]) {
          adjMat[i][j] = adjMat[j][i] = 1;
          archiUsati++; 
        }
      }
    }
    if (best_sol_num == -1 || (archiUsati < best_sol_num)) {
      if (check_sol(adjMat, nV, p, m, 0) == 0) {
        if (best_sol_num == -1) {
          best_sol = malloc(maxArchiDistinti * sizeof(int));
          for (i = 0; i < maxArchiDistinti; i++)
            best_sol[i] = elencoArchi[i];
          best_sol_num = archiUsati;
        } else if (best_sol_num > archiUsati) {
          for (i = 0; i < maxArchiDistinti; i++)
            best_sol[i] = elencoArchi[i];
          best_sol_num = archiUsati;
        }
      }
    }
    freeMatrix(nV, adjMat);
    return;
  }

  // Genera tutti gli elementi del powerset di archi...
  elencoArchi[pos] = 0;
  trovaArchi_r(nV, p, m, pos+1, elencoArchi, maxArchiDistinti);
  elencoArchi[pos] = 1;
  trovaArchi_r(nV, p, m, pos+1, elencoArchi, maxArchiDistinti);
}

void trovaArchi(int nV, int p, int m) {
  int nArchi = nV * (nV -1) / 2;
  int *archi = malloc(nArchi * sizeof(int));

  trovaArchi_r(nV, p, m, 0, archi, nArchi);
  if (best_sol_num != -1) {
    int i, j, k=0;
    for (i = 0; i < nV-1; i++) {
      for (j = i+1; j < nV; j++) {
        if (best_sol[k++]) {
            printf("%s %s\n", TSleggiIndice(elencoNodi, i), 
                    TSleggiIndice(elencoNodi, j));
        }
      }
    }
  } else {
      printf("Nessun soluzione trovata\n");
  }
  free(archi);
}

int main(int argc, char **argv) {
  if (argc != 4) 
    exit(-1);
  int p = atoi(argv[2]), m = atoi(argv[3]);
  int nV = leggiNodi(argv[1]);
  trovaArchi(nV, p, m);
  TSlibera(elencoNodi);
  return 0;
}
