//
// Created by simone on 11/11/22.
//

#ifndef UNTITLED3_PERSONAGGI_H
#define UNTITLED3_PERSONAGGI_H

#include "inventario.h"
#include <stdlib.h>
#include <stdio.h>
#define MAXN 50
#define MAXNEQ 8

typedef struct{
    unsigned int hp;
    unsigned int mp;
    unsigned int atk;
    unsigned int def;
    unsigned int nag;
    unsigned int spr;
}statP_t;

typedef struct{
    int inUso;
    ItemO *vettEq;
}tabEquip_t;

typedef struct{
    char codice[MAXN];
    char nome[MAXN];
    char classe[MAXN];
    tabEquip_t equip;
    statP_t stat;
}ItemP;


typedef struct nodoPg *nodePg_t;
typedef struct{
    ItemP val;
    nodePg_t next;
}nodoPg;

typedef struct tabPg_t* nodeptabPg;
typedef struct{
    int nPg;
    nodoPg* headPg;
    nodoPg* tailPg;
}tabPg;

tabPg* leggifilepersonaggi(tabPg *tabp);
tabPg *leggitastierapersonaggio(tabPg *tabp);
void stampapersonaggi(tabPg *tabp);
void inputpersonaggifile(FILE *fp,ItemP *personaggi);
void inputpersonaggitastiera(ItemP *personaggi);
tabPg* allocazioneinizialepersonaggio();
void aggiungipersonaggio(tabPg *tabp,ItemP personaggi);
void ricercacodicepersonaggio(tabPg *tabp);
void eliminapersonaggio(tabPg *tabp);
#endif //UNTITLED3_PERSONAGGI_H

