#include "vertice.h"

Vertice VERTICEread(FILE *f){
   Vertice v;
   if(fscanf(f, "%s", v.nome)==1){
      v.grado=0;
      return v;
   }
   return VERTICEsetNull();
}


Vertice VERTICEsetNull(){
   Vertice v;
   strcpy(v.nome, "");
   v.grado=-1;
   return v;
}


Boolean VERTICEisNull(Vertice v){
   if(strcmp(v.nome, "")==0 && v.grado==-1)
      return VERO;
   return FALSO;
}


void VERTICEincrementaGrado(Vertice *v){
   (v->grado)++;
   return;
}


void VERTICEdecrementaGrado(Vertice *v){
   (v->grado)--;
   return;
}


void VERTICEazzeraGrado (Vertice *v){
    v->grado=0;
    return;
}
