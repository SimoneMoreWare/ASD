//
// Created by simone on 08/12/22.
//

#include "datetime.h"

int KEYcmp(Key k1, Key k2){
    if (k1>k2)
        return 1;
    else if (k1==k2)
        return 0;
    return -1;
}

Key KEYget(datetime val) {
    return val.anno*10000 + val.mese*100 + val.giorno;
}
