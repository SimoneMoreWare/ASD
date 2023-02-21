#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#define N 9

int perm_sempl(int pos, int *val, int *sol, int *mark, int num_cifre, char *n1, char *n2, char *n3);
int check(int num_cifre, int *sol, char *n1, char *n2, char *n3);

int main(int argc, char **argv) {

  int num_cifre = -1;
  char *n1, *n2, *n3;
  int sol[N] = {0};
  int val[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int mark[N] = {0};

  if (argc <= 4) {
    printf("Uso: %s <N> <addendo1> <addendo2> <somma>\n", argv[0]);
    exit(-1);
  }
  num_cifre = atoi(argv[1]);
  n1 = strdup(argv[2]);
  n2 = strdup(argv[3]);
  n3 = strdup(argv[4]);

  perm_sempl(0, val, sol, mark, num_cifre,  n1, n2, n3);
  free(n1);
  free(n2);
  free(n3);
  return 0;
}

int perm_sempl(int pos, int *val, int *sol, int *mark, int num_cifre,  char *n1, char *n2, char *n3) {
  int i;
  if (pos >= N)
    return check(num_cifre, sol, n1, n2, n3);

  for (i=0; i<N; i++)
    if (mark[i] == 0) {
      mark[i] = 1;
      sol[pos] = val[i];
      if (perm_sempl(pos+1, val, sol, mark, num_cifre, n1, n2, n3) ==1)
        return 1;
      mark[i] = 0;
    }
  return 0;
}

int check(int num_cifre, int *sol, char *n1, char *n2, char *n3) {

  int i, j, k = 0, ok = 0;
  int add1, add2, sum;
  char **nums = malloc (3*sizeof(char*));
  if (nums == NULL)
    return ok;
  nums[0] = strdup(n1);
  nums[1] = strdup(n2);
  nums[2] = strdup(n3);

  if (nums[0] == NULL || nums[1] == NULL || nums[2] == NULL)
    return ok;

  /* Assunzione: ci sono ESATTAMENTE 9 spazi da riempire ridistribuiti tra i due addendi e il risultato */
  for(i=0;i<3 && k<N; i++) {
    for(j=0;j<num_cifre && k<N; j++) {
      if (nums[i][j] == '_')
        nums[i][j] = sol[k++]+'0';
    }
  }

  add1 = atoi(nums[0]);
  add2 = atoi(nums[1]);
  sum = atoi(nums[2]);

  free(nums[0]);
  free(nums[1]);
  free(nums[2]);
  free(nums);

  ok = ((add1+add2) == sum);
  if(ok)
    printf("Una soluzione e': %d + %d = %d\n", add1, add2, sum);
  return ok;
}
