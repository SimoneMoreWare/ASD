#include <stdio.h>

unsigned  long fact(int n);

int main() {
  int n;

  printf("Input n (<=12):  ");
  scanf("%d", &n);

  printf("factorial of %d is: %lu \n", n, fact(n));

  return 0;
}

unsigned long  fact(int  n) {
  unsigned long  tot = 1;
  int i;

  for(i=2; i<=n; i++)
	tot = tot * i;

  return tot;
}
