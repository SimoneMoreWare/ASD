#include <stdio.h>
#include <stdlib.h>

#define V 8

int BinSearch(int v[], int l, int r, int k);

int main() {
  int i, index, k, v[V];

  for (i=0; i<V; i++) {
    printf("Input v[%d]:", i);
    scanf("%d", &v[i]);
  }

  printf("Input key:  ");
  scanf("%d", &k);

  index = BinSearch(v, 0, i-1, k);
  if (index != -1)
    printf("Key found at index: %d\n", index);
  else
    printf("Key not found\n");

  return 0;
}

int BinSearch(int v[], int l, int r, int k) {
  int m;
  if (l > r)
    return -1;

  m = (l + r) / 2;

  if (k == v[m])
    return (m);

  if (k < v[m])
    return BinSearch(v, l, m-1, k);

  return BinSearch(v, m+1, r, k);
}
