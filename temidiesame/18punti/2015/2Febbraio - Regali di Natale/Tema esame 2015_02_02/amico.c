#include "amico.h"

Amico AMICOread(FILE *f){
   Amico a;
   if(fscanf(f, "%s", a.nome)==1){
      a.regalo=EMPTY;
      return a;
   }
   return AMICOsetNull();
}


Amico AMICOsetNull(){
   Amico a;
   strcpy(a.nome, "");
   a.regalo=EMPTY;
   return a;
}


Boolean AMICOisNull(Amico a){
   if(a.regalo==EMPTY && strcmp(a.nome, "")==0)
      return VERO;
   return FALSO;
}
