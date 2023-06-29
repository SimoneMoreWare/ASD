#include "vertice.h"

Vertice VERTICEread(FILE *f){
    Vertice v;
    fscanf(f, "%s %f %f", v.id, &v.x, &v.y);
    return v;
}


void VERTICEprint(Vertice v, FILE *f){
   fprintf(f, "%s", v.id);
   return;
}
