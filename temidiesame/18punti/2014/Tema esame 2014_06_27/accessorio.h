#ifndef ACCESSORIO_H_INCLUDED
#define ACCESSORIO_H_INCLUDED
#define MAX 101
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char nome[MAX];
    float costo;
}Accessorio;

typedef enum{VERO, FALSO}Boolean;

Accessorio ACCESSORIOread(FILE *f);
Accessorio ACCESSORIOsetNull();
Boolean ACCESSORIOisNull(Accessorio a);
void ACCESSORIOprint(Accessorio a, FILE *f);

#endif // ACCESSORIO_H_INCLUDED
