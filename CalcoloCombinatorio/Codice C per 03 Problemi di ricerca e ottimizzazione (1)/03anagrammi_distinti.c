#include <stdio.h>
#include <stdlib.h>
#define MAX 40

int coeff_multin(int pos, char *dist_val, char *sol, int *mark, int n,  int n_dist, int count);
void Merge(char *val, int l, int q, int r);
void MergeSort(char *val, int l, int r);

int main(void) {
  int i, j, n, n_dist, total, *mark;
  char *val, *dist_val, *sol;

  printf("Inserisci n: ");
  scanf("%d", &n);
  val = malloc((n+1) * sizeof(char));
  dist_val = malloc((n+1) * sizeof(char));
  sol = malloc((n+1) * sizeof(char));

  printf("Inserisci stringa: ");
  scanf("%s", val);

  printf("Le permutazioni distinte della stringa %s con ripetizioni sono: \n", val);

  MergeSort(val, 0, n-1);

  n_dist =1;
  for (i=1; i<n; i++)
    if(val[i-1] != val[i])
      n_dist++;

  mark = calloc(n_dist, sizeof(int));

  j = 0;
  dist_val[j++] = val[0];
  for (i=1; i<n; i++)
    if(val[i-1] != val[i]) {
      dist_val[j++]= val[i];
    }
  dist_val[j] = '\0';

  i = 1;
  j = 0;
  mark[j] = 1;
  while(i < n) {
    while (val[i-1] == val[i]) {
      i++;
      mark[j]++;
    }
    j++;
    mark[j]++;
    i++;
  }

  for (i=0; i < n; i++)
    sol[i]= -1;

  total = coeff_multin(0, dist_val, sol, mark, n, n_dist, 0);
  printf("\ne in totale sono %d \n", total);

  return 0;
}

int coeff_multin(int pos, char dist_val[], char sol[], int mark[], int n, int n_dist, int count) {
  int i;
  if (pos >= n) {
    sol[pos]='\0';
    printf("\nSoluzione: ");
    printf("%s \n \n", sol);
    return count+1;
  }

  for (i=0; i<n_dist; i++)
    if (mark[i] > 0) {
      mark[i]--;
      sol[pos] = dist_val[i];
      count = coeff_multin(pos+1, dist_val, sol, mark, n, n_dist, count);
      mark[i]++;
    }
  return count;
}

void Merge(char *val, int l, int q, int r) {
  int i, j, k;
  char B[MAX];

  i = l;
  j = q+1;
  for(k = l; k <= r; k++)
    if (i > q)
      B[k] = val[j++];
    else if (j > r)
      B[k] = val[i++];
    else if (( val[i] < val[j]) || (val[i] == val[j])  )
      B[k] = val[i++];
    else
      B[k] = val[j++];
  for ( k = l; k <= r; k++ )
    val[k] = B[k];
  return;
}

void MergeSort(char *val, int l, int r) {
  int q;
  if (r <= l)
    return;
  q = (l + r)/2;
  MergeSort(val, l, q);
  MergeSort(val, q+1, r);
  Merge(val, l, q, r);
}

