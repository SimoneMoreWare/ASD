#ifndef E1_QUOTAZIONE_H
#define E1_QUOTAZIONE_H

#include "time.h"
#include <stdio.h>

typedef struct quotazione_{
    data_t data;
    float val;
    int q;
}quotazione;

quotazione quotazioneNEW(data_t d);
void quotazioneStore(FILE *out, quotazione t);
data_t quotazioneGetData(quotazione t);
float quotazioneGetVal(quotazione t);
int quotazioneCheckNull(quotazione t);
quotazione quotazioneSetNull();

#endif
