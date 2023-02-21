#include<stdlib.h>
#include<stdio.h>
#define N 16

int check(int *val, int k, int *s, int l);
void ps(int pos, int *v, int *s, int k, int *ml, int *bs);


int main(void) {

  int i, v[N] = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15}, s[N], bs[N], ml = 0;

  ps(0, v, s, N, &ml, bs);

  printf("One of the longest increasing sequences has length %d and is: \n ", ml);
  printf("{ ");
  for (i=0; i<N; i++)
    if (bs[i]!=0)
      printf("%d ", v[i]);
  printf("}\n");

  return 0;
}

void ps(int pos, int *v, int *s, int k, int *ml, int *bs) {
  int j, l=0, ris;

  if (pos >= k) {
    for (j=0; j<k; j++)
      if (s[j]!=0)
        l++;
    ris = check(v, k, s, l);
    if (ris==1)
      if (l >= *ml) {
        for (j=0; j<k; j++)
          bs[j] = s[j];
        *ml = l;
      }
    return;
  }

  s[pos] = 0;
  ps(pos+1, v, s, k, ml, bs);
  s[pos] = 1;
  ps(pos+1, v, s, k, ml, bs);
  return;
}

int check(int *v, int k, int *s, int l) {
  int i=0,j, t, ok=1;

  for (t=0; t<l-1; t++){
    while ((s[i]==0) && (i < k-1))
      i++;
    j=i+1;
    while ((s[j]==0) && (j < k))
      j++;
    if (v[i] >= v[j])
      ok = 0;
    i = j;
   }
   return ok;
 }

