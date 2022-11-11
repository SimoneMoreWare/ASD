//
// Created by simone on 11/11/22.
//

#ifndef UNTITLED3_PERSONAGGI_H
#define UNTITLED3_PERSONAGGI_H

#include "inventario.h"
#include <stdlib.h>

// Lista non ordinata come quasi ADT in violazione della regola 2
//manca il typedef e non c'è il parametro list l...
typedef struct nodeP* linkP;
struct nodeP{
    int val;
    linkP next;
};

void listInsHeadP(linkP *head,int val);
void listDisplayP(linkP p);
#endif //UNTITLED3_PERSONAGGI_H

