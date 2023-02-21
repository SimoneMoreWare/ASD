#include <stdlib.h>
#include <stdio.h>
#include "aeroporti.h"
#include "voli.h"

int main (int argc, char **argv) {
  aeroporti_t *tabA;
  voli_t *tabV;

  tabA = leggiAeroporti(argv[1]);
  if (tabA==NULL) return 1;
  tabV = leggiVoli(argv[2], tabA);
  if (tabV==NULL) return 1;

  scriviAeroporti("stdout", tabA);
  scriviVoli("stdout", tabV);

  liberaAeroporti(tabA);
  liberaVoli(tabV);

  return (0);
}
