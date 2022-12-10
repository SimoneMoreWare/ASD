//
// Created by simone on 08/12/22.
//

#ifndef UNTITLED16_DATETIME_H
#define UNTITLED16_DATETIME_H



typedef int Key;

typedef struct{
    int anno,mese,giorno; //ora e minuti non servono, li skippo nel file
}datetime;
int KEYcmp(Key k1, Key k2);
Key KEYget(datetime val);


#endif //UNTITLED16_DATETIME_H
