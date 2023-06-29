#include "menu.h"

Menu MENUinit(int P){
    Menu m;
    m.costo=0;
    m.P=P;
    m.piatti=(int*)malloc(P*sizeof(int));
    if(m.piatti==NULL)
       exit(EXIT_FAILURE);
    return m;
}


Menu MENUcreate(int P, int *piatti, float costo){
    int i;
    Menu m=MENUinit(P);
    for(i=0; i<P; i++)
       m.piatti[i]=piatti[i];
    m.costo=costo;
    return m;
}


void MENUprint(Menu m, Piatti p, FILE *f){
    int i;
    Piatto piatto;
    fprintf(f, "Costo: %.2f\n", m.costo);
    for(i=0; i<m.P; i++){
        piatto=PIATTIgetPiatto(p, m.piatti[i]);
        PIATTOprint(piatto, f);
    }
    return;
}


Simboli MENUcompare(Menu m1, Menu m2){
    int i;
    if(m1.costo < m2.costo)
       return PRIMA;
    else if(m1.costo > m2.costo)
       return DOPO;
    else if(m1.costo==m2.costo){
       for(i=0; i<m1.P; i++){
          if(m1.piatti[i]<m2.piatti[i])
             return PRIMA;
          else if(m1.piatti[i]>m2.piatti[i])
             return DOPO;
       }
    }
    return UGUALE;
}


Menu MENUsetNull(){
    Menu m;
    m.piatti=NULL;
    m.costo=0;
    m.P=0;
    return m;
}


void MENUclear(Menu m){
    if(m.piatti!=NULL)
       free(m.piatti);
    return;
}
