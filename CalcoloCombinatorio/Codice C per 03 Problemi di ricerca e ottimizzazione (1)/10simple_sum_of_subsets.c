#include <stdio.h>
#include <stdlib.h>
#define MAX 10

void powerset(int pos, int *val, int *sol, int k, int X);
int check(int *sol, int *val, int X, int k);

int main(void) {
  int i, k, X, *val, *sol;

  printf("Input number of elements: ");
  scanf("%d", &k);

  val = malloc(k*sizeof(int));
  sol = calloc(k,sizeof(int));

  printf("Input elements: \n");
  for (i=0; i<k; i++) {
    printf("val[%d] = ", i);
    scanf("%d", &val[i]);
  }

  printf("Input sum: ");
  scanf("%d", &X);

  printf("The subset(s) whose sum is %d is (are): \n", X);

  powerset(0, val, sol, k, X);

  free(val);
  free(sol);

  return 0;
}

void powerset(int pos, int *val, int *sol, int k, int X) {
  int j, out;

  if (pos >= k) {
    out = check(sol, val, X, k);
    if (out==1) {
      printf("{ \t");
      for (j=k-1; j>=0; j--)
        if (sol[j]!=0)
          printf("%d \t", val[k-j-1]);
        printf("} \n");
    }
    return;
  }

  sol[pos] = 0;
  powerset(pos+1, val, sol, k, X);
  sol[pos] = 1;
  powerset(pos+1, val, sol, k, X);
}

int check(int *sol, int *val, int X, int k) {
  int j, tot=0;
  printf("start solution\n");
  for (j=k-1; j>=0; j--)
    if (sol[j]!=0)
      tot += val[k-j-1];
  printf("end solution\n");
  if (tot==X)
    return 1;
  else
    return 0;
}
