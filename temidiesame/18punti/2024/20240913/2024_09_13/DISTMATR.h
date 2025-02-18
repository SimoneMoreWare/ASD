#ifndef DISTMATR_H
#define DISTMATR_H
#include <stdio.h>
#include <stdlib.h>

// dimenticato * per puntatore 
typedef struct distmatr_t *DISTMATR;

DISTMATR DISTMATRinit(int N);
DISTMATR DISTMATRfile(FILE* file, DISTMATR d);
int DISTMATRgetN(DISTMATR d);
int DISTMATRgetVal(DISTMATR d, int i, int j);

#endif