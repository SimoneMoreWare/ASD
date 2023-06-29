#include "posizione.h"

Posizione POSIZIONEcrea(int lun, int r, int c, char dir){
    Posizione p;
    p.lun=lun;
    p.r=r;
    p.c=c;
    p.dir=dir;
    return p;
}

void POSIZIONEprint(Posizione p, FILE *f){
    fprintf(f, "%d %d %d %c\n", p.lun,p.r, p.c, p.dir);
}
