#include <stdio.h>

unsigned long tr_fact(int n, unsigned  long f);

int main() {
  int  n;

  printf("Input n (<=12):  ");
  scanf("%d", &n);

  printf("factorial of %d is: %lu \n", n, tr_fact(n, 1));
  return 0;
}

unsigned long  tr_fact(int  n, unsigned  long f) {
  if(n == 0)
    return f;
  return tr_fact(n-1, n*f);
}
