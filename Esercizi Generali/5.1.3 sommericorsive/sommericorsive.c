#include <stdlib.h>
#include <stdio.h>

int somma(int n) {
  if (n <= 0)
    return 0;
  return n%10 + somma(n/10);
}

int main(void) {
  int num;

  printf("Inserire numero: ");
  scanf("%d", &num);
  printf("La somma delle cifre di %d e' %d\n", num, somma(num));
  return 0;
}
