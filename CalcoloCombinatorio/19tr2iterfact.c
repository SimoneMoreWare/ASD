#include <stdio.h>

unsigned long  tr2iterfact(int  n, unsigned  long f);

int main() {
  int n;

  printf("Input n (<=12):  ");
  scanf("%d", &n);

  printf("factorial of %d is: %lu \n", n, tr2iterfact(n, 1));
  return 0;
}

unsigned  long tr2iterfact(int  n, unsigned  long f){
  while (n > 0) {
    f = n * f;
    n--;
  }
  return f;
}
