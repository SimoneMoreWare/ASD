#include "quotazione.h"

quotazione quotazioneNEW(data_t d){
    quotazione q;
    q.data = d;
    q.val = 0;
    q.q = 0;
    return q;
}
void quotazioneStore(FILE *out, quotazione t){
    printf("-");
    printData(t.data);
    fprintf(out," %.2f \n",quotazioneGetVal(t));
}

data_t quotazioneGetData(quotazione t){
    if(quotazioneCheckNull(t))
        return quotazioneSetNull().data;
    return t.data;
}

float quotazioneGetVal(quotazione t){
    if(t.q != 0)
        return t.val / (float)t.q;
    return -1.0;
}

int quotazioneCheckNull(quotazione t){
    return (t.q == 0);
}
quotazione quotazioneSetNull(){
    quotazione q = {{-1,-1,-1}, 0.0, 0};
    return q;
}
