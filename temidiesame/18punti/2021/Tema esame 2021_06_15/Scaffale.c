#include "Scaffale.h"

struct scaffale_s{
    char codice[CAR];
    Slot slots[K];
    int nPacchi;
};



Scaffale SCAFFALEinit(){
    Scaffale s;
    int i;
    s=(Scaffale)malloc(sizeof(struct scaffale_s));
    if(s==NULL){
        printf("Errore di allocazione.");
        exit(EXIT_FAILURE);
    }
    for(i=0; i<K; i++){
        s->slots[i]=SLOTsetNull();
    }
    s->nPacchi=0;
    return s;
}


Scaffale SCAFFALEread(FILE *f){
    Scaffale s=SCAFFALEinit();
    fscanf(f, "%s", s->codice);
    return s;
}


Scaffale SCAFFALEsetNull(){
    Scaffale s=NULL;
    return s;
}


Boolean SCAFFALEisEmpty(Scaffale s){
    if(s==NULL)
        return VERO;
    return FALSO;
}


char *SCAFFALEgetCode(Scaffale s){
    return s->codice;
}


Boolean SCAFFALEinserisciPacco(Scaffale s, Pacco *pa, Posizione po){
    if(po.slot<0 || po.slot>=K){
        printf("\nImpossibile posizionare il pacco %s: lo slot %d non esiste.\n", PACCOgetCode(pa), po.slot);
        return FALSO;
    }
    if(SLOTisOccupato(s->slots[po.slot])==VERO){
        printf("\nImpossibile posizionare il pacco %s: lo slot %d e' gia' occupato.\n", PACCOgetCode(pa), po.slot);
        return FALSO;
    }
    SLOTinserisciPacco(&s->slots[po.slot], pa);
    PACCOsetPosizione(pa, po.corridoio, po.scaffale, po.slot);
    (s->nPacchi)++;
    return VERO;
}


void SCAFFALEeliminaPacco(Scaffale s, Pacco *pa, Posizione p){
    SLOTeliminaPacco(&s->slots[p.slot]);
    PACCOsvuotaPosizione(pa);
    (s->nPacchi)--;
    return;
}


Boolean SCAFFALEcompatta(Scaffale s1, int corridoio1, Scaffale s2, int corridoio2){
    int i, j;
    Posizione po;
    Pacco *pa;
    if(s1->nPacchi + s2->nPacchi >K){
        printf("\nImpossibile compattare il contenuto degli scaffali %s e %s: il numero totale di pacchi %d eccede il numero massimo di slot %d.\n", s1->codice, s2->codice, (s1->nPacchi + s2->nPacchi), K);
        return FALSO;
    }
    for(i=0; i<K; i++){
        if(SLOTisOccupato(s2->slots[i])==VERO){
            pa=SLOTgetPacco(s2->slots[i]);
            for(j=0; j<K; j++){
                if(SLOTisOccupato(s1->slots[j])==FALSO){
                    SCAFFALEinserisciPacco(s1, pa, POSIZIONEcrea(corridoio1, s1->codice, j));
                    PACCOsetPosizione(pa, corridoio1, s1->codice, j);
                    (s1->nPacchi)++;
                    break;
                }
            }
        }
    }
    SCAFFALEsvuota(s2);
    return VERO;
}


void SCAFFALEsvuota(Scaffale s){
    int i;
    for(i=0; i<K; i++){
        if(SLOTisOccupato(s->slots[i])==VERO)
            SLOTeliminaPacco(&(s->slots[i]));
    }
    s->nPacchi=0;
    return;
}


void SCAFFALEprint(Scaffale s, FILE *f){
    int i;
    fprintf(f, "%s", s->codice);
    if(s->nPacchi>0){
        fprintf(f, " (SLOT PIENI:");
        for(i=0; i<K; i++){
            if(SLOTisOccupato(s->slots[i])==VERO){
                fprintf(f, " S%d", i);
            }
        }
        fprintf(f, ")");
    }
    return;
}


void SCAFFALEfree(Scaffale s){
    if(s!=NULL){
        free(s);
    }
    return;
}
