#include "vertice.h"

Vertice VERTICEcrea(char *vertice){
    Vertice v;
    strcpy(v.vertice, vertice);
    v.inDegree=0;
    v.outDegree=0;
    return v;
}


void VERTICEincrementaOutDegree(Vertice *v){
   (v->outDegree)++;
   return;
}


void VERTICEincrementaInDegree(Vertice *v){
   (v->inDegree)++;
   return;
}
