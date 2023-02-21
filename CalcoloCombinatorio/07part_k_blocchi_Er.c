
#include <stdio.h>
#include <stdlib.h>



void SP_rec(int n, int k, int m, int p, int *sol, int *val, FILE *fout);
void SetPartitions(int n, int k, int *sol, int *val, FILE *fout);

int main(void){
  int i, n, k, *val, *sol;
  FILE *fout;

  fout =fopen("out.txt", "w");
  printf("\n");
  printf("\nCalcolo delle partizioni di un insiemi di n elementi in k blocchi\n");
  printf("Inserisci il numero n di elementi: ");
  scanf("%d", &n);
  printf("Inserisci il numero k di blocchi: ");
  scanf("%d", &k);

  val = malloc(n * sizeof(int));
  sol = calloc(n, sizeof(int));

  for (i=0; i<n; i++) {
    printf("Inserisci elementi: ");
    scanf("%d", &val[i]);
  }

  printf("Le partizioni di %d elementi in %d blocchi sono nel file out.txt\n", n, k);

  SetPartitions(n, k, sol, val, fout);

  free(val);
  free(sol);

  return 0;
}

void SetPartitions(int n, int k, int *sol, int *val, FILE *fout) {
  SP_rec(n, k, 0, 0, sol, val, fout);
  return;
}

void SP_rec(int n, int k, int m, int pos, int *sol, int *val, FILE *fout) {
  int i, j;
  if (pos >= n) {
    if (m == k) {
      for (i=0; i<m; i++) {
        fprintf(fout, "{ ");
        for (j=0; j<n; j++) {
          if (sol[j]==i)
            fprintf(fout, "%d ", val[j]);
        }
        fprintf(fout, "}  ");
     }
      fprintf(fout, "\n");
    }
    return;
  }

  for (i=0; i<m; i++) {
    sol[pos] = i;
    SP_rec(n, k, m, pos+1, sol, val, fout);
  }
  sol[pos] = m;
  SP_rec(n, k, m+1, pos+1, sol, val, fout);
}

