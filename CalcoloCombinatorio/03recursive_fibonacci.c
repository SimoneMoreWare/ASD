#include <stdio.h>

unsigned long fib(int n);

int main() {
  int n;

  printf("Input n:  ");
  scanf("%d", &n);

  printf("Fib(%d) = %lu \n", n, fib(n));

  return 0;
}

unsigned long fib(int n) {
  if(n == 0 || n == 1)
    return(n);

  return(fib(n-2) + fib(n-1));
}

