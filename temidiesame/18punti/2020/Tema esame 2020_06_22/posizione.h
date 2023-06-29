#ifndef POSIZIONE_H_INCLUDED
#define POSIZIONE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int lun, r, c;
      char dir;
}Posizione;

Posizione POSIZIONEcrea(int lun, int r, int c, char dir);
void POSIZIONEprint(Posizione p, FILE *f);

#endif // POSIZIONE_H_INCLUDED
