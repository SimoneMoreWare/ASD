#include "schema.h"

Schema SCHEMAread(FILE *f){
    int i, lun, r, c;
    char dir;
    Schema s;

    fscanf(f, "%d %d %d", &s.nr, &s.nc, &s.dim);
    s.posizioni=(Posizione*)malloc(s.dim*sizeof(Posizione));
    if(s.posizioni==NULL)
         exit(-1);
    for(i=0; i<s.dim; i++){
        fscanf(f, "%d %d %d %c%*c", &lun, &r, &c, &dir);
        s.posizioni[i]=POSIZIONEcrea(lun, r, c, dir);
    }
    return s;
}

void SCHEMAclear(Schema s){
   if(s.posizioni!=NULL)
        free(s.posizioni);
}
