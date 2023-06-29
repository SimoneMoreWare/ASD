#include "accessorio.h"
#include <string.h>

Accessorio ACCESSORIOread(FILE *f){
    Accessorio a;
    if(fscanf(f, "%s %f", a.nome, &a.costo)==2){
       return a;
    }
    return ACCESSORIOsetNull();
}


Accessorio ACCESSORIOsetNull(){
    Accessorio a;
    strcpy(a.nome, "");
    a.costo=-1;
    return a;
}


Boolean ACCESSORIOisNull(Accessorio a){
    if(strcmp(a.nome, "")==0 && a.costo==-1)
       return VERO;
    return FALSO;
}


void ACCESSORIOprint(Accessorio a, FILE *f){
    fprintf(f, "\t\t%s %.2f\n", a.nome, a.costo);
    return;
}
