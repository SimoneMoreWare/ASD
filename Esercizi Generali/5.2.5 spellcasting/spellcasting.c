#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check(char *sol) {
  if (sol[0] == 'R' || sol[1] == 'R' || sol[5] == 'R')
    return 0;
  return 1;
}

void perm_rip(int pos, char *dist_val, char *sol, int *mark, int n, int n_dist) {
  int i;
    if (pos >= n) {
      if (check(sol)) {
        printf("%s\n", sol);
        return;
      }
      return;
    }

  for(i=0; i<n_dist; i++) {
    if (mark[i] > 0) {
      sol[pos] = dist_val[i];
      mark[i]--;
      perm_rip(pos+1, dist_val, sol, mark, n, n_dist);
      sol[pos] = '\0';
      mark[i]++;
    }
  }
  return;
}

int main(int argc, char *argv[]) {
    int n, n_dist = 3, *mark;

    char dist_val[3] = {'B', 'R', 'V'};

    char *sol = calloc(n+1, sizeof(char));
    if (sol == NULL)
      return -1;
    mark = calloc(n_dist, sizeof(int));
    if (mark == NULL)
      return -1;

    printf("Inserisci il numero di rune: ");
    scanf("%d", &n);
    printf("Inserisci il numero di rune blu: ");
    scanf("%d", &mark[0]);
    printf("Inserisci il numero di rune rosse: ");
    scanf("%d", &mark[1]);
    printf("Inserisci il numero di rune verdi: ");
    scanf("%d", &mark[2]);

    perm_rip(0, dist_val, sol, mark, n, n_dist);
    free(sol);
    free(mark);
    return 0;
}
