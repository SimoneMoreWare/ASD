#include "vertice.h"

Vertice VERTICEcrea(char *nome){
   Vertice v;
   strcpy(v.nome, nome);
   v.grado=0;
   return v;
}

void VERTICEsetGrado(Vertice *v, int grado){
    v->grado=grado;
    return;
}

void VERTICEprint(Vertice v, FILE *f){
    fprintf(f, "%s", v.nome);
    return;
}
