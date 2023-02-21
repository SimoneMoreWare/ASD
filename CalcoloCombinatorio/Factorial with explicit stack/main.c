#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#define N 100

unsigned long fact(int n);

int main() {
  int n;
  printf("Input n (<=12):  ");
  scanf("%d", &n);
  printf("factorial of %d is: %lu \n", n, fact(n));
  return 0;
}

unsigned  long fact (int n){
  unsigned  long f = 1;
  S stack;
  stack = STACKinit(N);

  while (n>0) {
    STACKpush(stack, n);
    n--;
  }

  while (STACKsize(stack) > 0) {
    n = STACKpop (stack);
    f = n * f;
  }
  return f;
}
