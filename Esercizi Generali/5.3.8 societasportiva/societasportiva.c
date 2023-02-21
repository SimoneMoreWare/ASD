#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#define fn "in.txt"
#define MAXC 21

typedef struct ex_ {
  char *nome;
  int kcal;
  int n_fasi;
  int *fasi;
} ex;

ex* leggi_file(int *n_es) {
  ex *e = NULL;
  int i, j;
  char es_name[MAXC];
  FILE *in = fopen(fn, "r");

  fscanf(in, "%d", n_es);
  e = calloc(*n_es, sizeof(ex));

  for(i=0; i<*n_es; i++) {
    fscanf(in, "%s %d %d", es_name, &e[i].kcal, &e[i].n_fasi);
    e[i].nome = strdup(es_name);
    e[i].fasi = calloc(e[i].n_fasi, sizeof(int));
    for(j=0; j<e[i].n_fasi; j++)
      fscanf(in, "%d", &e[i].fasi[j]);
  }
  fclose(in);
  return e;
}

void plan(int n, int k, int pos, int *sol, ex *e, int N, int M, int *num_es_fase, int *cal_fase, int *best_sol, int *delta) {
  int i, f, TOT = 0;
  if (pos >= n) {
    for(i=1; i<k; i++) {
      TOT += cal_fase[i];
      if (cal_fase[i] == 0)
        return;
    }
    if (*delta == -1 || ((k-1)*M-TOT) < *delta) {
      *delta = (k-1)*M-TOT;
      for(i=0; i<n; i++)
        best_sol[i] = sol[i];
    }
    return;
  }

  for (i=0; i<=e[pos].n_fasi; i++) {
    if (i<e[pos].n_fasi)
      f = e[pos].fasi[i];
    else f = 0; /* includi la fase 0 (esercizio non utilizzato) */
	if ((cal_fase[f]+e[pos].kcal <= M) && (num_es_fase[f] < N)) {
      cal_fase[f] += e[pos].kcal;
      num_es_fase[f]++;
      sol[pos] = f;
      plan(n, k, pos+1, sol, e, N, M, num_es_fase, cal_fase, best_sol, delta);
      num_es_fase[f]--;
      cal_fase[f] -= e[pos].kcal;
    }
  }
  return;
}

int main(int argc, char **argv) {
  int n_es = 0, n_fasi = 4, N, M, i, j, t, delta = -1;
  ex *e = leggi_file(&n_es);
  int *sol = calloc(n_es, sizeof(int));
  int *best_sol = calloc(n_es, sizeof(int));
  int *num_es_fase = calloc(n_fasi+1, sizeof(int));
  int *cal_fase = calloc(n_fasi+1, sizeof(int));

  printf("Inserisci numero max di esercizi per fase: ");
  scanf("%d", &N);

  printf("Inserisci numero calorie obiettivo: ");
  scanf("%d", &M);

  plan(n_es, n_fasi+1, 0, sol, e, N, M, num_es_fase, cal_fase, best_sol, &delta);


  for (i=1; i<=n_fasi; i++) {
    t = 0;
    printf("Fase %d\n", i);
    for (j=0; j<n_es; j++) {
      if (best_sol[j] == i) {
        printf("\t%s\n", e[j].nome);
        t += e[j].kcal;
      }
    }
    printf("\tTOT = %d\n", t);
  }
  printf("Delta_TOT = %d\n", delta);
  for(i=0; i<n_es; i++) {
    free(e[i].nome);
    free(e[i].fasi);
  }
  free(e);
  free(sol);
  free(best_sol);
  free(num_es_fase);
  free(cal_fase);
  return 0;
}
