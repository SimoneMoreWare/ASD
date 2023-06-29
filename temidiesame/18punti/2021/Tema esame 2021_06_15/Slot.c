#include "Slot.h"

Slot SLOTsetNull(){
    Slot s;
    s.occupato=FALSO;
    s.pacco=NULL;
    return s;
}


Boolean SLOTisOccupato(Slot s){
    return s.occupato;
}


void SLOTinserisciPacco(Slot *s, Pacco *p){
    s->pacco=p;
    s->occupato=VERO;
    return;
}


void SLOTeliminaPacco(Slot *s){
    *s=SLOTsetNull();
    return;
}


Pacco *SLOTgetPacco(Slot s){
    return (s.pacco);
}
