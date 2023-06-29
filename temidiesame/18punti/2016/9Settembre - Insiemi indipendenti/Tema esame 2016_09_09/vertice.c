#include "vertice.h"

Vertice VERTICEread(FILE *f){
   Vertice v;
   if(fscanf(f, "%s", v.identificatore)==1)
      return v;
   return VERTICEsetNull();
}


Vertice VERTICEsetNull(){
   Vertice v;
   strcpy(v.identificatore, "");
   return v;
}


void VERTICEprint(Vertice v, FILE *f){
    fprintf(f, "%s", v.identificatore);
    return;
}


Boolean VERTICEisNull(Vertice v){
   if(strcmp(v.identificatore, "")==0)
      return VERO;
   return FALSO;
}
