#include <stdio.h>

int coeffbin(int n, int k){
  int i, res = 1;
  for (i = 0; i < k; i++)
    res = res * (n--) / (i+1);
  return res;
}

long Bell(int n){
  int k;
  long sum = 0;
  if (n==0)
    return 1;
  for (k=0; k<n; k++)
    sum += coeffbin(n-1, k) * Bell(k);
  return sum;
}

int main () {
    int n;
    do {
        printf("Inserisci n: ");
        scanf("%d", &n);
    } while(n<0);

    printf("Bell(%d) = %lu\n", n, Bell(n));
    return 0;
}
