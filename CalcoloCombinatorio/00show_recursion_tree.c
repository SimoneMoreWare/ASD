#include <stdio.h>
#define MAX 32
#include <math.h>
#define DBG 0

void show(int x[], int l, int r);

int main() {
  int i, n;
  int x[MAX];

  printf("Input n = 2^k: ");
  scanf("%d", &n);

  printf("Input  array \n");
  for(i=0; i<n; i++) {
    printf("x[%d] = ", i);
    scanf("%d", &x[i]);
  }

#if DBG
  printf("The array is: ");
  for(i=0; i<n; i++)
    printf("%d", x[i]);
  printf("\n");
#endif
  show(x, 0, n-1);
  return 0;
}

void show(int x[], int l, int r) {
  int i, c;

  if(l >= r)
    return;

  c = (r+l)/2;

  printf("xs = ");
  for (i=l; i <= c; i++)
    printf("%d", x[i]);
  printf("\n");

  show(x, l, c);

  printf("xd = ");
  for (i=c+1; i <= r; i++)
    printf("%d", x[i]);
  printf("\n");

  show(x, c+1, r);

  return;
}
