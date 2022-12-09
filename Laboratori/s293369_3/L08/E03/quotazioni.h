//
// Created by simone on 08/12/22.
//

#ifndef UNTITLED16_QUOTAZIONI_H
#define UNTITLED16_QUOTAZIONI_H

#include "datetime.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    datetime data;
    float valore;
    int quantitatransiozioni;
}Quotazione;

typedef struct  binarysearchtree *BST;

Quotazione ITEMsetNull();
BST BSTinit();
Quotazione QuotazioneScan(FILE *fp);
void BSTinsert_leafI(BST bst, Quotazione x);
void readbst(BST bstq,FILE *fp);
void QuotationStore(Quotazione val);
#endif //UNTITLED16_QUOTAZIONI_H
