#include "parole.h"
#include <string.h>

Parole PAROLEcrea(){
	int i;
	Parole p;
	for(i=0; i<MAX; i++)
		p.parole[i]=WORDLUNinit();
	return p;
}

Parole PAROLEread(FILE *f){
	Parole p=PAROLEcrea();
	int dim, i;
    char parola[MAX+1];

	fscanf(f, "%d", &dim);
    for(i=0; i<dim; i++){
	    fscanf(f, "%s", parola);
	    WORDLUNinsertWord(&p.parole[strlen(parola)-1], WORDcrea(parola));
	}
	return p;
}

void PAROLEclear(Parole p){
    int i;
    for(i=0; i<MAX; i++)
        WORDLUNfree(p.parole[i]);
    return;
}
