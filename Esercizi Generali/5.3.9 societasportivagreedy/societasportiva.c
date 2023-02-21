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

void swap(ex *e, int i, int j) {
  ex tmp = e[i];
  e[i] = e[j];
  e[j] = tmp;
  return;
}

int partition(ex *e, int l, int r) {
  int i = l-1, j = r;
  ex x = e[r];
  for(;;) {
    while (e[++i].kcal > x.kcal);
    while (e[--j].kcal < x.kcal)
      if (j == l)
        break;
    if (i >= j)
      break;
    swap(e, i, j);
  }
  swap(e, i, r);
  return i;
}

void quicksort(ex *e, int l, int r) {
  int q;
  if (r <= l)
    return;
  q = partition(e, l, r);
  quicksort(e, l, q-1);
  quicksort(e, q+1, r);
  return;
}

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

int infase(ex *e, int esercizio, int fase) {
  int i;
  for (i=0; i<e[esercizio].n_fasi; i++)
    if (e[esercizio].fasi[i] == fase) return 1;
  return 0;
}

/*
 Ordina gli esercizi per valore descrescente, assegna l'esercizio corrente alla prima fase ammissibile del suo elenco.
*/
void greedy1(ex *e, int n_es, int n_fasi, int N, int M, int *sol, int *num_es_fase, int *cal_fase) {
  int i, j;
  quicksort(e, 0, n_es-1);
  for (i=0; i<n_es; i++) {
    for (j=1; j<=n_fasi; j++) {
      if (infase(e, i, j)) {
        if(num_es_fase[j] < N && ((cal_fase[j]+e[i].kcal) <= M)) {
          sol[i] = j;
          num_es_fase[j]++;
          cal_fase[j] += e[i].kcal;
          break;
        }
      }
    }
  }
  return;
}

/*
 Ordina gli esercizi per valore descrescente, assegna l'esercizio corrente alla fase ammissible meno carica del suo elenco.
*/
void greedy2(ex *e, int n_es, int n_fasi, int N, int M, int *sol, int *num_es_fase, int *cal_fase) {
  int i, j, min, minj;
  quicksort(e, 0, n_es-1);
/*  qsort(e, n_es, sizeof(ex), cmpInc); */
  for(i=0;i<n_es;i++) {
    minj = -1;
    min = -1;
    for(j=1;j<=n_fasi;j++) {
      if (!infase(e, i, j) || num_es_fase[j] >= N || ((cal_fase[j]+e[i].kcal) > M)) continue;
      if (minj == -1 || (min > cal_fase[j])) {
        minj = j;
        min = cal_fase[j];
      }
    }
    if (minj != -1) {
      sol[i] = minj;
      num_es_fase[minj]++;
      cal_fase[minj] += e[i].kcal;
    }
  }
  return;
}


/*
 Ordina gli esercizi per valore descrescente, assegna alla fase meno carica l'esercizio più vantaggioso ancora disponibile.
*/

void greedy3(ex *e, int n_es, int n_fasi, int N, int M, int *sol, int *num_es_fase, int *cal_fase) {
  int i, j, again, min, mini;
  quicksort(e, 0, n_es-1);
  do {
    again = 0;
    mini = -1;
    min = 0;
    for(i=1;i<=n_fasi;i++) {
      if (num_es_fase[i] >= N)
        continue;
      if (mini == -1 || min > cal_fase[i]) {
        mini = i;
        min = cal_fase[i];
      }
    }
    if (mini != -1) {
      /* Non si sa se la fase corrente, seppur a carico minimo, ammetta altri esercizi.
         Per evitare che l'esecuzione sia interrotta troppo preso porta comunque again a 1,
         eventualmente escludendola in seguito dalle scelte possibili (vedi commento sotto) */
      again = 1;
      for(j=0;j<n_es;j++) {
        if (sol[j])
          continue;
        if (!infase(e, j, mini))
          continue;
        if (cal_fase[mini]+e[j].kcal > M)
          continue;
        sol[j] = mini;
        num_es_fase[mini]++;
        cal_fase[mini] += e[j].kcal;
        break;
      }
      /* Se la fase minima non ha altre scelte possibili, la si rende "non selezionabile" artificialmente.
         Le altre fasi potrebbero avere ancora del potenziale, per cui occorre considerarle almeno un'altra volta ciascuna.*/
      if (j == n_es)
        num_es_fase[mini] = N;
    }
  } while(again);
  return;
}



int main(int argc, char **argv) {
  int n_es = 0, n_fasi = 4, N, M, i, j, t, T;
  ex *e = leggi_file(&n_es);
  int *sol = calloc(n_es, sizeof(int));
  int *num_es_fase = calloc(n_fasi+1, sizeof(int));
  int *cal_fase = calloc(n_fasi+1, sizeof(int));

  printf("Inserisci numero max di esercizi per fase: ");
  scanf("%d", &N);

  printf("Inserisci numero calorie obiettivo: ");
  scanf("%d", &M);

  greedy2(e, n_es, n_fasi, N, M, sol, num_es_fase, cal_fase);

  T = 0;
  for (i=1; i<=n_fasi; i++) {
    t = 0;
    printf("Fase %d\n", i);
    for (j=0; j<n_es; j++) {
      if (sol[j] == i) {
        printf("\t%s\n", e[j].nome);
        t += e[j].kcal;
      }
    }
    printf("\tTOT = %d\n", t);
    T += t;
  }
  printf("Delta_TOT = %d\n", n_fasi*M-T);
  for(i=0; i<n_es; i++) {
    free(e[i].nome);
    free(e[i].fasi);
  }
  free(e);
  free(sol);
  free(num_es_fase);
  free(cal_fase);
  return 0;
}
