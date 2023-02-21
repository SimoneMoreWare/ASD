#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "titolo.h"
#include "quotazioni.h"

struct titolo_{
    char *cod;
    float min, max;
    BSTquotazioni bst;
};

char *getKey(titolo t){
    return t->cod;
}

titolo titoloNEW(char *cod){
    titolo t;
    t = malloc(sizeof(*t));
    t->cod = strdup(cod);
    t->min = t->max = -1.0;
    t->bst = BSTquotazioneInit();
    return t;
}

void titoloStore(FILE *out, titolo t){
    if(t == NULL)
        return;
    fprintf(out, "%s: MIN=%.2f MAX=%.2f\n",t->cod,t->min, t->max);
    BSTquotazioniStore(out, t->bst);
    printf("\n\n");
}

int titolocmp(char *t1, char *t2){
    return strcmp(t1,t2);
}

quotazione ricercaQuotazione(titolo t, data_t d){
    return BSTquotazioniSearch(t->bst, d);
}

static void updateMinMax(titolo t){
    float min = -1.0, max = -1.0;
    BSTquotazioniGetMinMax(t->bst, &min, &max);
    t->min = min;
    t->max = max;
}

void titoloInsertTransazione(titolo t, data_t d, float val, int qta){
    BSTquotazioniInsert(t->bst, d, val, qta);
    updateMinMax(t);
}

void titolominMaxRange(titolo t, float *min, float *max, data_t d1, data_t d2){
    *min = *max = -1.0;
    BSTquotazioniGetMinMaxRange(t->bst, min, max, d1, d2);
}

void titoloMinMax(titolo t, float *min, float *max){
    data_t d1,d2;
    d1 = BSTgetMindata(t->bst);
    d2 = BSTgetMaxdata(t->bst);
    BSTquotazioniGetMinMaxRange(t->bst, min, max, d1, d2);
}

void titolobilancia(titolo t, int s){
    int diff;
    if( (diff =BSTgetDiff(t->bst)) > s){
        printf("Bilancio il bst. %d\n",diff);
        BSTbalance(t->bst);
    }
    printf("Il bst non necessita di bilanciamento, diff = %d\n", diff);
    return;
}