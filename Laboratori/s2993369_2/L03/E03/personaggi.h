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
    int hp;
    int mp;
    int atk;
    int def;
    int nag;
    int spr;
}statP_t;

typedef struct{
    int inUso;
    ItemO vettEq[MAXNEQ];
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

typedef struct{
    int nPg;
    nodoPg* headPg;
    nodoPg* tailPg;
}tabPg;

tabPg* leggifilepersonaggi(tabPg *tabp);
tabPg *leggitastierapersonaggio(tabPg *tabp);
tabPg *aggiungereequipaggiamento(tabPg *tabp, tabInv_t *tabi);
tabPg *rimuovereequipaggiamento(tabPg *tabp, tabInv_t *tabi);
void stampapersonaggi(tabPg *tabp);
void stampaequippagiamentopersonaggio(nodoPg *nodo,int i);
void inputpersonaggifile(FILE *fp,ItemP *personaggi);
void inputpersonaggitastiera(ItemP *personaggi);
tabPg* allocazioneinizialepersonaggio();
void aggiungipersonaggio(tabPg *tabp,ItemP personaggi);
void ricercacodicepersonaggio(tabPg *tabp);
void eliminapersonaggio(tabPg *tabp);
void inserireoggettonellequipaggiamento(nodoPg *nodo,tabInv_t *tabi, int indexfind, char *ricercato);
void eliminareoggettonellequipaggiamento(nodoPg *nodo, int indexfind, char *ricercato);
void calcolostat(tabPg *tabp);
void freeTabella(tabPg *tabp);
void stampapersonaggiosingolo(nodoPg *nodo);
int ifemptylist(tabPg *tabp);
#endif //UNTITLED3_PERSONAGGI_H

