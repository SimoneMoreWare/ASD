//
// Created by simone on 11/11/22.
//

#ifndef UNTITLED3_INVENTARIO_H
#define UNTITLED3_INVENTARIO_H
/*
typedef struct node *linkO;
typedef struct{
    char nome[MAXN];
    char tipologia[MAXN];
    int stat[6];
}ItemO;*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 50

typedef struct{
    int hp;
    int mp;
    int atk;
    int def;
    int nag;
    int spr;
}statO_t;

typedef struct{
    char nome[MAXN];
    char tipo[MAXN];
    statO_t stat;
}ItemO;

typedef struct{
    ItemO *vettInv;
    int nlnv;
    int maxlnv;
}tabInv_t;

tabInv_t* leggifileinventario();
tabInv_t *allocainventario (int dim_inventario);
void inputinventariofile(FILE *fp,tabInv_t **tutto,int i);
void stampainventario(tabInv_t *tabi);
int ricercanomeoggetto(tabInv_t *tabi);
void stampaoggettotrovato(tabInv_t *tabi,int index);

#endif //UNTITLED3_INVENTARIO_H
