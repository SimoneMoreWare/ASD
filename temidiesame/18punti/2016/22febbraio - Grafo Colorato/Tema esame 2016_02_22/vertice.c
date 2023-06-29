#include "vertice.h"

Vertice VERTICEread(FILE *f){
   char colore[6];
   Vertice v;
   if(fscanf(f, "%s %s", v.identificatore, colore)==2){
      v.colore=(strcmp(colore, "ROSSO")==0)?ROSSO:NERO;
      return v;
   }
   return VERTICEsetNull();
}


Vertice VERTICEsetNull(){
   Vertice v;
   v.colore=-1;
   strcpy(v.identificatore, "");
   return v;
}


Boolean VERTICEisNull(Vertice v){
   if(strcmp(v.identificatore, "")==0 && v.colore==-1)
      return VERO;
   return FALSO;
}
