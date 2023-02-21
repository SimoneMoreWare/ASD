#include <stdio.h>

unsigned long fact(int n);

int main() {
  int n;

  printf("Input n (<=12):  ");
  scanf("%d", &n);

  printf("factorial of %d is: %lu \n", n, fact(n));
  return 0;
}

unsigned long fact(int n) {

  if((n == 0) || (n == 1))
	return 1;
  return n*fact(n-1);
}
