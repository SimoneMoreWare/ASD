#include "articolo.h"

Articolo ARTICOLOread(FILE *f){
    Articolo a;
    fscanf(f, "%s %s %d %s", a.nome, a.relatore, &a.slot, a.argomento);
    return a;
}

void ARTICOLOprint(Articolo a, FILE *f){
    fprintf(f, "%s", a.nome);
    return;
}
