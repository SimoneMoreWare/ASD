#include <stdio.h>
#include <stdlib.h>
#define MAXN 11
#define DBG 0

unsigned long fib(int n, unsigned long *knownF);

int main() {
  int i, n;
  unsigned long *knownF;

  knownF = malloc((MAXN+1)*sizeof(unsigned long));
  for (i=0; i<MAXN; i++)
    knownF[i]= -1;

  do {
    printf("Input n (-1 to exit, max %d):  ", MAXN-1);
    scanf("%d", &n);
    printf("Fibonacci of %d is: %lu \n", n, fib(n, knownF));
#if DBG
    for (i=0; i<=n; i++)
      printf("knownf[%d]= %d\n", i, knownF[i]);
#endif
  } while (n != -1);
  return 0;
}

unsigned long fib(int n, unsigned long *knownF) {
  unsigned long t;
  if (knownF[n] != -1)
    return knownF[n];
  if(n == 0 || n == 1) {
    knownF[n] = n;
    return(n);
  }
  t = fib(n-2, knownF) + fib(n-1, knownF);
  knownF[n] = t;
  return t;
}
