#ifndef E1_QUOTAZIONI_H
#define E1_QUOTAZIONI_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "time.h"
#include "quotazione.h"

typedef struct BSTquotazioni_ *BSTquotazioni;

BSTquotazioni BSTquotazioneInit();
int BSTquotazioniEmpty(BSTquotazioni bst);
void BSTquotazioniInsert(BSTquotazioni bst, data_t d, float val, int q);
quotazione BSTquotazioniSearch(BSTquotazioni bst, data_t d);
void BSTquotazioniGetMinMax(BSTquotazioni bst, float *min, float *max);
void BSTquotazioniStore(FILE *out, BSTquotazioni bst);
void BSTquotazioniGetMinMaxRange(BSTquotazioni bst, float *min, float *max, data_t d1, data_t d2);
data_t BSTgetMindata(BSTquotazioni bst);
data_t BSTgetMaxdata(BSTquotazioni bst);
int BSTgetDiff(BSTquotazioni bst);
void BSTbalance(BSTquotazioni bst);
#endif //E1_QUOTAZIONI_H
