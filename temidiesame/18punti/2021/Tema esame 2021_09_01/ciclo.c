#include "ciclo.h"

Ciclo CICLOread(FILE *f){
    Ciclo c;
    int i;
    if(fscanf(f, "%d", &c.nVertici)==1){
        c.vertici=(int*)malloc(c.nVertici*sizeof(int));
        if(c.vertici==NULL) exit(EXIT_FAILURE);
        for(i=0; i<c.nVertici; i++)
            fscanf(f, "%d", &c.vertici[i]);
        return c;
     }
    return CICLOsetNull();
}

Ciclo CICLOsetNull(){
     Ciclo c;
     c.nVertici=-1;
     c.vertici=NULL;
     return c;
}

Boolean CICLOisNull(Ciclo c){
      if(c.nVertici==-1 && c.vertici==NULL)
          return VERO;
      return FALSO;
}

void CICLOprint(Ciclo c, FILE *f){
    int i;
    for(i=0; i<c.nVertici; i++){
        fprintf(f, "%d ", c.vertici[i]);
    }
}
