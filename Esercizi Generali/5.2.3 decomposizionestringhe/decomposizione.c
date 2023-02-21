#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#define N 3

void decomponiR(char *str, int lunghstr, int pos, int *lunghezze, int nstr, int *sol, int indsol) {
  int i, k = 0;
  if (pos == lunghstr) {
    printf("Decomposizione: ");
    for(i=0;i<indsol;i++) {
      printf("%.*s ", lunghezze[sol[i]], str+k);
      k += lunghezze[sol[i]];
    }
    printf("\n");
    return;
  }
  for(i=0;i<nstr;i++) {
    if (pos + lunghezze[i] <= lunghstr) {
      sol[indsol] = i ;
      decomponiR(str, lunghstr, pos+lunghezze[i], lunghezze, nstr, sol, indsol+1);
    }
  }
}

void decomponi(char *str, int nstr, int *lunghezze) {
  int lunghstr = strlen(str);
  int *sol = calloc(lunghstr, sizeof(int));
  decomponiR(str, lunghstr, 0, lunghezze, nstr, sol, 0);
  free(sol);
}

int main(int argc, char **argv) {
  int lunghezze[N] = {2, 5, 7};
  char *str = "tentativo";
  decomponi(str, N, lunghezze);
  return 0;
}
