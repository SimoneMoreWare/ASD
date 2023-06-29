#ifndef SLOT_H_INCLUDED
#define SLOT_H_INCLUDED
#include "Pacco.h"

typedef struct{
    Pacco *pacco;
    Boolean occupato;
}Slot;

Slot SLOTsetNull();
Boolean SLOTisOccupato(Slot s);
void SLOTinserisciPacco(Slot *s, Pacco *p);
void SLOTeliminaPacco(Slot *s);
Pacco *SLOTgetPacco(Slot s);

#endif // SLOT_H_INCLUDED
