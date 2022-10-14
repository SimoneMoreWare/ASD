#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int anagrammi(int pos, char sol[], char val[], int mark[], int n,  int count);

int main() {
  char *val, *sol;
  int n, *mark, total;

  printf("Inserisci la  lunghezza della stringa n =\n");
  scanf("%d", &n);
  val = malloc(n+1 * sizeof(char));
  sol = malloc(n+1 * sizeof(char));
  mark = calloc(n, sizeof(int));

  printf("Inserisci la  stringa di sole lettere minuscole:\n");
  scanf("%s", val);

  printf("Gli anagrammi con eventuali  ripetizioni di %s  sono:\n", val);
  total = anagrammi(0, sol, val, mark, n, 0);
  printf("e in totale sono %d \n", total);

  free(val);
  free(sol);

  return 0;
}

int anagrammi(int pos, char sol[], char val[], int mark[], int n,  int count) {
  int i;

  if (pos >= n) {
    sol[pos] = '\0';
    printf("%s\n", sol);
    return count+1;
  }
  for (i=0; i<n; i++)
    if (mark[i] == 0) {
      mark[i] = 1;
      sol[pos] = val[i];
      count = anagrammi(pos+1, sol, val, mark,   n,  count);
      mark[i] = 0;
    }
  return count;
}
