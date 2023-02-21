#include <stdio.h>
#include <stdlib.h>


int powerset_disp_rip(int pos, int *val, int *sol, int n, int count);
int powerset_div_conq(int pos, int *val, int *sol, int n, int start, int count);
int powerset_comb_semp(int* val, int n, int* sol);
int powerset_r(int* val, int k, int* sol, int n, int pos, int start);

int main(void) {
  int i, n, cnt, *val, *sol;

  printf("Input number of elements: ");
  scanf("%d", &n);

  val = malloc(n*sizeof(int));
  sol = calloc(n,sizeof(int));

  printf("Input elements: \n");
  for (i=0; i<n; i++) {
    printf("val[%d] = ", i);
    scanf("%d", &val[i]);
  }

  printf("The powerset of set {");
  for(i =0; i<n; i++)
    printf(" %d ", val[i]);
  printf(" } is \n");

  printf("arrangements with repetitions\n");
  cnt = powerset_disp_rip(0, val, sol, n, 0);
  printf ("number of sets: %d \n", cnt);

  printf("divide and conquer\n");
  cnt = powerset_div_conq(0, val, sol, n, 0, 0);
  printf ("number of sets: %d \n", cnt);

  printf("simple combinations\n");
  cnt = powerset_comb_semp(val, n, sol);
  printf ("number of sets: %d \n", cnt);

  free(val);
  free(sol);

  return 0;
}

int powerset_disp_rip(int pos, int *val, int *sol, int n, int count) {
  int i;

  if (pos >= n) {
    printf("{ ");
    for (i=0; i<n; i++)
      if (sol[i]!=0)
        printf("%d ", val[i]);
      printf("} \n");
      return count+1;
  }

  sol[pos] = 0;
  count = powerset_disp_rip(pos+1, val, sol, n, count);
  sol[pos] = 1;
  count = powerset_disp_rip(pos+1, val, sol, n, count);
  return count;
}

int powerset_div_conq(int pos, int *val, int *sol, int n, int start, int count) {
   int i;
   if (start >= n) {
      printf("{ ");
       for (i = 0; i < pos; i++)
         printf("%d ", sol[i]);
      printf("} \n");
      return count+1;
   }
   for (i = start; i < n; i++) {
      sol[pos] = val[i];
      count = powerset_div_conq(pos+1, val, sol, n, i+1, count);
   }
   count = powerset_div_conq(pos, val, sol, n, n, count);
   return count;
}

int powerset_comb_semp(int* val, int n, int* sol){
   int count = 0, j;
   printf("{ }\n");
   count++;
   for(j = 1; j <= n; j++){
      count += powerset_r(val, n, sol, j, 0, 0);
   }
   return count;
}

int powerset_r(int* val, int n, int* sol, int j,
               int pos, int start){
   int count = 0, i;
   if (pos >= j){
      printf("{ ");
      for (i = 0; i < j; i++)
         printf("%d ", sol[i]);
      printf("}\n");
      return 1;
   }
   for (i = start; i < n; i++){
      sol[pos] = val[i];
      count += powerset_r(val, n, sol, j, pos+1, i+1);
   }
   return count;
}
