#include "dipendente.h"

Dipendente DIPENDENTEread(FILE *f){
    Dipendente d;
    fscanf(f, "%d %s %s %d %d %d %d", &d.matricola, d.cognome, d.nome, &d.competenze[OPERAIO], &d.competenze[AMMINISTRATIVO], &d.competenze[TECNICO], &d.competenze[INFORMATICO]);
    return d;
}

