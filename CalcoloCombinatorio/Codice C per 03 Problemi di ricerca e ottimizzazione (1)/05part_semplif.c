#include <stdio.h>
#include <stdlib.h>

void disp_ripet(int pos, int *val, int *sol, int n, int k);

int main(void){
  int i, n, k, *sol, *val;

  printf("\n");
  printf("\nCalcolo delle partizioni (semplificate) di n oggetti in k blocchi\n");
  printf("Inserisci il numero n di oggetti: ");
  scanf("%d", &n);
  printf("Inserisci il numero k di blocchi: ");
  scanf("%d", &k);

  val = malloc(n * sizeof(int));
  sol = malloc(n * sizeof(int));
  for (i=0; i < n; i++)
    sol[i]= -1;

  for (i=0; i<n; i++) {
    printf("Inserisci elementi: ");
    scanf("%d", &val[i]);
  }

  printf("Le partizioni di %d oggetti  su %d blocchi sono \n", n, k);
  printf("Attenzione: non si eliminano le simmetrie!\n");

  disp_ripet(0, val, sol, n, k);

  free(val);
  free(sol);

  return 0;
}

void disp_ripet(int pos, int *val, int *sol, int n, int k) {
  int i, j, ok=1, *occ;


  if (pos >= n) {
    occ = calloc(k, sizeof(int));
    for (j=0; j<n; j++)
       occ[sol[j]]++;
    i=0;
    while ((i < k) && ok) {
        if (occ[i]==0)
          ok = 0;
        i++;
    }
    if (ok == 0)
      return;
    else {
      printf("partizione: ");
      for (i=0; i<k; i++) {
        printf("{ ");
        for (j=0; j<n; j++) {
          if (sol[j]==i)
            printf("%d ", val[j]);
        }
        printf("}  ");
      }
      printf("\n");
      return;
   }
   free(occ);
  }
  for (i = 0; i < k; i++) {
    sol[pos] = i;
    disp_ripet(pos+1, val, sol, n, k);
  }
}

