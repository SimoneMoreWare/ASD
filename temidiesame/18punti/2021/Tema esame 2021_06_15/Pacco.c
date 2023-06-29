#include "Pacco.h"
#include <string.h>

//---POSIZIONE---
Posizione POSIZIONEcrea(int corridoio, char *scaffale, int slot){
    Posizione p;
    p.corridoio=corridoio;
    p.slot=slot;
    strcpy(p.scaffale, scaffale);
    return p;
}


Posizione POSIZIONEsetNull(){
    Posizione p;
    p.corridoio=-1;
    p.slot=-1;
    strcpy(p.scaffale, "");
    return p;

}


Boolean POSIZIONEisEmpty(Posizione p){
    if(p.corridoio==-1 && p.slot==-1 && strcmp(p.scaffale, "")==0)
        return VERO;
    return FALSO;
}


void POSIZIONEprint(Posizione p, FILE *f){
    if(POSIZIONEisEmpty(p)==VERO){
        fprintf(f, "POSIZIONE VUOTA.\n");
    }
    else{
        fprintf(f, "CORRIDOIO: %d - SCAFFALE: %s - SLOT: %d.\n", p.corridoio, p.scaffale, p.slot);
    }
    return;
}



//---PACCO---
Pacco PACCOread(FILE *f){
    char codice[CAR];
    Pacco p=PACCOsetNull();

    if(fscanf(f, "%s", codice)==1){
        strcpy(p.codice, codice);
        p.pos=POSIZIONEsetNull();
        return p;
    }
    return p;
}


void PACCOsetPosizione(Pacco *p, int corridoio, char *scaffale, int slot){
    p->pos=POSIZIONEcrea(corridoio, scaffale, slot);
    return;
}


void PACCOsvuotaPosizione(Pacco *p){
    p->pos=POSIZIONEsetNull();
    return;
}


Pacco PACCOsetNull(){
    Pacco p;
    strcpy(p.codice, "");
    p.pos=POSIZIONEsetNull();
    return p;
}


Boolean PACCOisNull(Pacco p){
    if(strcmp(p.codice, "")==0 && POSIZIONEisEmpty(p.pos)==VERO)
        return VERO;
    return FALSO;
}


char *PACCOgetCode(Pacco *p){
    return p->codice;
}


void PACCOprintPosizione(Pacco p, FILE *f){
    fprintf(f, "\nIl pacco %s e' posizionato in: ", p.codice);
    POSIZIONEprint(p.pos, f);
}


void PACCOprintCode(Pacco p, FILE *f){
    fprintf(f, "%s", p.codice);
    return;
}

Posizione PACCOgetPosizione(Pacco p){
    return p.pos;
}
