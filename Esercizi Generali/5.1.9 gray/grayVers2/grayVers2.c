#include <stdlib.h>
#include <stdio.h>

void gray(int *codice, int pos, int n, int primo) {
  int i, secondo = (primo+1) % 2; /* 1->0, 0->1 */
  if (pos == n) {
    for (i=0; i<n; i++)
      printf("%d", codice[i]);
    printf("\n");
    return;
  }
  codice[pos] = primo;
  gray(codice, pos+1, n, 0);
  codice[pos] = secondo;
  gray(codice, pos+1, n, 1);
}

int  main(int argc, char **argv) {
    int n = atoi(argv[1]);
    int *codice = calloc(n, sizeof(int));
    gray(codice, 0, n, 0);
    free(codice);
    return 0;
}

