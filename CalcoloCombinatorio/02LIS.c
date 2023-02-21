#include<stdlib.h>
#include<stdio.h>
#define N 16

int check(int *val, int k, int *sol, int len);
void powerset(int pos, int *val, int *sol, int k, int *maxlen, int *bestsol);


int main(void) {

  int i, val[N] = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15}, sol[N], bestsol[N], maxlen = 0;

  powerset(0, val, sol, N, &maxlen, bestsol);

  printf("One of the longest increasing sequences has length %d and is: \n ", maxlen);
  printf("{ ");
  for (i=0; i<N; i++)
    if (bestsol[i]!=0)
      printf("%d ", val[i]);
  printf("}\n");

  return 0;
}

void powerset(int pos, int *val, int *sol, int k, int *maxlen, int *bestsol) {
  int j, len=0, ris;

  if (pos >= k) {
    for (j=0; j<k; j++)
      if (sol[j]!=0)
        len++;
    ris = check(val, k, sol, len);
    if (ris==1)
      if (len >= *maxlen) {
        for (j=0; j<k; j++)
          bestsol[j] = sol[j];
        *maxlen = len;
      }
    return;
  }

  sol[pos] = 0;
  powerset(pos+1, val, sol, k, maxlen, bestsol);
  sol[pos] = 1;
  powerset(pos+1, val, sol, k, maxlen, bestsol);
  return;
}

int check(int *val, int k, int *sol, int len) {
  int i=0,j, t, ok=1;

  for (t=0; t<len-1; t++){
    while ((sol[i]==0) && (i < k-1))
      i++;
    j=i+1;
    while ((sol[j]==0) && (j < k))
      j++;
    if (val[i] > val[j])
      ok = 0;
    i = j;
   }
   return ok;
 }

