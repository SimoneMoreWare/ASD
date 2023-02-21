#include <stdlib.h>
#include <stdio.h>

#define NUM   10
#define ALPHA 26

void converti(int n, int b, char *sym) {
  if (n < b) {
    printf("%c", sym[n]);
    return;
  }
  converti(n/b, b, sym);
  printf("%c", sym[n%b]);
}

int main(int argc, char **argv) {
  char *sym;
  int i, n, b;

  if (argc != 3) {
	printf("Uso: %s n b\n", argv[0]);
	return -1;
  }

/* Usa un vettore di simboli per la stampa delle singole cifre. Rende possibile coprire conversione fino a base 62.
   Le cifre non sono memorizzate. Si usa solo la ricorsione per generare/stampare il numero convertito cifra per cifra. */
  sym = calloc(NUM+ALPHA+ALPHA, sizeof(char));

  for (i=0; i<NUM; i++)
    sym[i] = '0'+i;
  for (i=0; i<ALPHA; i++)
    sym[i+NUM] = 'A'+i;
  for (i=0; i<ALPHA; i++)
    sym[i+NUM+ALPHA] = 'a'+i;

  n = atoi(argv[1]);
  b = atoi(argv[2]);

  converti(n, b, sym);
  printf("\n");

  return 0;
}
