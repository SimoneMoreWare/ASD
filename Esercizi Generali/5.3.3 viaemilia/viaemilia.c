#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<stdio.h>
#include<math.h>

#define MAX 20+1
#define DBG 1

typedef struct citta_ {
  char *nome;
  int dist, pop;
} citta_t;

citta_t *leggiFile(char *filename, int *nc) {
  int i, d, p;
  char c[MAX];
  citta_t *vc;
  FILE *in = fopen(filename, "r");
  if (in == NULL)
    return NULL;

  fscanf(in, "%d", nc);
  vc = calloc(*nc, sizeof(citta_t));
  if(vc == NULL)
    return NULL;

  for(i=0;i<*nc;i++) {
    fscanf(in, "%s %d %d", c, &p, &d);
    vc[i].nome = strdup(c);
    if(vc[i].nome == NULL)
      return NULL;
    vc[i].dist = d;
    vc[i].pop  = p;
  }
  fclose(in);
  return vc;
}

int **mutuaDistanza(citta_t *c, int n) {
  int i, j, **mat = calloc(n, sizeof(int*));
  if (mat == NULL)
    return NULL;
  for(i=0;i<n;i++) {
    mat[i] = calloc(n, sizeof(int));
    if (mat[i] == NULL)
      return NULL;
  }

  for(i=0;i<n;i++) {
    for(j=i+1;j<n;j++) {
      mat[i][j] = mat[j][i] = abs(c[i].dist - c[j].dist);
    }
  }

#if DBG
  for(i=0;i<n;i++) {
    for(j=0;j<n;j++) {
      printf("%5d", mat[i][j]);
    }
    printf("\n");
  }
  printf("\n");
#endif

  return mat;
}

int SommaDistanze(citta_t *c, int n, int k, int *sol, int **mat_dist) {
  /* Calcolo del valore SomDist minimo eseguendo due scansioni del vettore di distanze dagli ATO, una da destra e una da sinistra
     propagando opportunamente i valori */
  int i, d, *distMin = calloc(n, sizeof(int));
  /* Inizializza tutte le città a distanza infinita */
  for(i=0;i<n;i++)
    distMin[i] = INT_MAX;
  /* Se una città ospita un ATO, inizializza la sua distanza a 0 */
  for(i=0;i<k;i++)
    distMin[sol[i]] = 0;

  /* Scansione verso DX */
  for(i=1;i<n;i++) {
    /* Se la città immediatamente a SX (i-1) ha distanza infinita da un ATO, ignorala */
    if (distMin[i-1] == INT_MAX)
      continue;
    /* Se la città immediatamente a SX (i-1) ha una distanza non infinita da un ATO, considera la sua distanza da tale ATO e aggiungi
       il costo per transitare dalla città i-1 a questa (città i) */
    d = distMin[i-1] + mat_dist[i-1][i];
    /* Se la distanza della città i da un ATO è peggiore rispetto alla distanza di (i-1) più il tratto che separa i e i-1, aggiorna */
    distMin[i] = (d < distMin[i]) ? d : distMin[i];
  }

  /* Scansione verso SX (stessa logica di cui sopra) */
  for(i=n-2;i>=0;i--) {
    if (distMin[i+1] == INT_MAX)
      continue;
    d = distMin[i+1] + mat_dist[i+1][i];
    distMin[i] = (d < distMin[i]) ? d : distMin[i];
  }

  /* Aggiungi il contributo della popolazione al calcolo delle distanze e calcola il complessivo */
  for(i=0, d=0;i<n;i++) {
    d += distMin[i]*c[i].pop;
  }

  free(distMin);
  return d;
}

void ATO_r(citta_t *citta, int n, int k, int pos, int start, int *sol, int *best_sol, int *min, int **mat_dist) {
  int i, SomDist;

  if (pos >= k) { /* Condizione di terminazione */
    SomDist = SommaDistanze(citta, n, k, sol, mat_dist); /* Calcolo del valore SomDist per la soluzione appena generata */
    if (SomDist < *min) {  /* Se è migliorante, aggiorna */
#if DBG
      printf("Miglioramento %d > %d\n", *min, SomDist);
#endif
      *min = SomDist;
      memcpy(best_sol, sol, k*sizeof(int));
    }
    return;
  }

  /* Generazione di combinazioni semplici di k elementi  */
  for(i=start;i<n;i++) {
    sol[pos] = i;
    ATO_r(citta, n, k, pos+1, i+1, sol, best_sol, min, mat_dist);
  }
}

int ATO(citta_t *citta, int n, int k, int **mat_dist) {
  int min = INT_MAX, i, *best_sol;
  /* Vettori di appoggio per la soluzione corrente e la soluzione migliore fin ora trovata */
  int *sol = calloc(k, sizeof(int));
  if (sol == NULL)
    exit(-1);
  best_sol = calloc(k, sizeof(int));
  if (best_sol == NULL)
    exit(-1);
  ATO_r(citta, n, k, 0, 0, sol, best_sol, &min, mat_dist);

  printf("Soluzione ottima: %d\n", min);
  for(i=0;i<k;i++)
    printf(" - %s\n", citta[best_sol[i]].nome);

  free(sol);
  free(best_sol);

  return min;
}

int main(int argc, char **argv) {
  /* Dichiarazioni */

  int n,i;
  int k;
  citta_t *citta;
  int **mat_dist;


  if(argc != 3) {
    printf("Uso: %s <file_citta> <k>\n", argv[0]);
    return -1;
  }


  /* Acquisizione dati */

  k = atoi(argv[2]);
  citta = leggiFile(argv[1], &n);
  if (citta == NULL)
    return -1;

  /* Calcolo distanze tra città */
  mat_dist = mutuaDistanza(citta, n);
  if (mat_dist == NULL)
    return -1;

  /* Generazione soluzione */
  printf("Soluzione a SomDist minima di valore: %d\n", ATO(citta, n, k, mat_dist));
  for(i=0;i<n;i++) {
    free(citta[i].nome);
    free(mat_dist[i]);
  }
  free(citta);
  free(mat_dist);
  return 0;
}
