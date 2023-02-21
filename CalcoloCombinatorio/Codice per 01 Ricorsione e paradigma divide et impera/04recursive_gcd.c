#include <stdio.h>

int gcd1(int x, int y);
int gcd2(int x, int y);

int main() {
  int x, y;
  printf("Input x and y:  ");
  scanf("%d%d", &x, &y);

  printf("Algorithm 1: gcd of %d and %d is: %d \n", x, y, gcd1(x, y));
  printf("Algorithm 2: gcd of %d and %d is: %d \n", x, y, gcd2(x, y));

  return 0;
}


int gcd1(int x, int y) {
  if(x == y)
    return x;
  if (x > y)
    return gcd1(x-y, y);
  else
    return gcd1(x, y-x);
}

int gcd2(int x, int y) {
  if(y == 0)
    return x;
  return gcd2(y, x % y);
}

