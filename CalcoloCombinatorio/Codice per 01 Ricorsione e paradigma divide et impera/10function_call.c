#include <stdio.h>
#include <stdlib.h>

int f1(int x);
int f2(int x);

int main() {
  int x, a=10;
  x = f1(a);
  printf("x is %d \n", x);
}

int f1(int x) {
  return f2(x);
}

int f2(int x) {
  return x+1;
}

