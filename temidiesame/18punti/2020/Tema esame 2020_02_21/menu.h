#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "piatti.h"

typedef enum{PRIMA, DOPO, UGUALE}Simboli;

typedef struct{
    int *piatti;
    int P;
    float costo;
}Menu;

Menu MENUcreate(int P, int *piatti, float costo);
Menu MENUinit(int P);
void MENUprint(Menu m, Piatti p, FILE *f);
Simboli MENUcompare(Menu m1, Menu m2);
Menu MENUsetNull();
void MENUclear(Menu m);


#endif // MENU_H_INCLUDED
