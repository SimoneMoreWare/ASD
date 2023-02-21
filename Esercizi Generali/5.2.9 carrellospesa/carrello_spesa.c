#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAXP 26


typedef struct prodotti_ {
  char *nome;
  float prezzo;
} prodotti_t;

prodotti_t *leggiProdotti(char *file, int *np) {
  int i;
  char nomep[MAXP];
  prodotti_t *vp;
  FILE *in;

  in = fopen(file, "r");
  if (in == NULL)
    return NULL;

  fscanf(in, "%d\n", np);
  vp = calloc(*np, sizeof(prodotti_t));
  if (vp == NULL)
    return NULL;

  for(i=0;i<*np;i++) {
    fscanf(in, "%s %f\n", nomep, &vp[i].prezzo);
    vp[i].nome = strdup(nomep);
  }
  fclose(in);
  return vp;
}

void comb_sempl(int pos, prodotti_t *vp, int *sol, int n, int k, int start, float B, float costo) {
  int i;
  if (pos >= k) {
    if (costo <= B) {
      for (i=0; i<k; i++)
        printf("%s ", vp[sol[i]].nome);
      printf(" con costo %.2f\n", costo);
    }
    return;
  }

  for (i=start; i<n; i++) {
    sol[pos] = i;
    costo += vp[i].prezzo;
    comb_sempl(pos+1, vp, sol, n, k, i+1, B, costo);
    costo -= vp[i].prezzo;
  }
  return;
}

int main(void) {

  int np = 0, i, *sol;
  int K;
  float B;

  prodotti_t *vp;

  vp = leggiProdotti("prodotti.txt", &np);
  if(vp == NULL || np <= 0)
    exit(-1);

  printf("Num. prodotti = %d\n", np);
  for(i=0;i<np;i++)
    printf("%s %.2f\n", vp[i].nome, vp[i].prezzo);

  printf("K = ");
  scanf("%d", &K);
  printf("B = ");
  scanf("%f", &B);

  sol = malloc(K * sizeof(int));
  for (i=0; i < K; i++)
    sol[i]= -1;

  for (i=K; i <= np; i++)
    comb_sempl(0, vp, sol, np, i, 0, B, 0.0);
  for(i=0;i<np;i++) {
    free(vp[i].nome);
  }
  free(vp);
  free(sol);

  return 0;
}

