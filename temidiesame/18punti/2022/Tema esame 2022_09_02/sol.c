#include "sol.h"
#include <string.h>

Posizione POSIZIONEsetNull(){
    Posizione p;
    p.r=-1;
    p.c=-1;
    p.dir='\0';
    return p;
}

Boolean POSIZIONEisEmpty(Posizione p){
    if(p.r==-1 && p.c==-1 && p.dir=='\0')
        return VERO;
    return FALSO;
}

Posizione POSIZIONEcrea(int r, int c, char dir){
    Posizione p;
    p.r=r;
    p.c=c;
    p.dir=dir;
    return p;
}

Posizione POSIZIONEread(FILE *f){
    Posizione p;
    fscanf(f, "%d %d %c", &p.r, &p.c, &p.dir);
    return p;
}

void POSIZIONEprint(Posizione p, FILE *f){
    fprintf(f, "%d %d %c", p.r, p.c, p.dir);
    return;
}



Scelta SCELTAcrea(char *parola, int rInizio, int cInizio, char direzione){
    Scelta s;
    strcpy(s.parola, parola);
    s.p=POSIZIONEcrea(rInizio, cInizio, direzione);
    return s;
}

Scelta SCELTAread(FILE *f){
    Scelta s;
    fscanf(f, "%s", s.parola);
    s.p=POSIZIONEread(f);
    return s;
}

void SCELTAprint(Scelta s, FILE *f){
    fprintf(f, "%s ", s.parola);
    POSIZIONEprint(s.p, f);
    return;
}


Sol SOLcrea(int maxD){
    Sol s;
    s.maxD=maxD;
    s.scelte=(Scelta*)malloc(maxD*sizeof(Scelta));
    if(s.scelte==NULL)
       exit(EXIT_FAILURE);
    s.nScelte=0;
    return s;
}

Sol SOLread(FILE *f){
   Sol s;
   int nScelte, i;
   fscanf(f, "%d", &nScelte);
   s=SOLcrea(nScelte);
   s.nScelte=nScelte;
   for(i=0; i<nScelte; i++)
      s.scelte[i]=SCELTAread(f);
   return s;
}

void SOLprint(Sol s, FILE *f){
    int i;
    for(i=0; i<s.nScelte; i++){
        SCELTAprint(s.scelte[i], f);
        fprintf(f, "\n");
    }
    return;
}

void SOLclear(Sol s){
    if(s.scelte!=NULL)
       free(s.scelte);
    return;
}
