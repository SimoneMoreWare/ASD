#include "time.h"
#include <stdio.h>

data_t getData(char *s){
    data_t tmp;
    sscanf(s,"%d/%d/%d", &tmp.a,&tmp.m,&tmp.g);
    return tmp;
}

void printData(data_t t){
    printf("%d/%d/%d",t.a,t.m,t.g);
}

static int sameYears(data_t d1, data_t d2){
    return (d1.a == d2.a);
}

static int sameMonths(data_t d1, data_t d2){
    return (d1.m == d2.m);
}

static int sameDays(data_t d1, data_t d2){
    return (d1.g == d2.g);
}

int datacmp(data_t d1, data_t d2){
    if(sameYears(d1,d2)){
        if(sameMonths(d1,d2)){
            if(sameDays(d1,d2))
                return 0;
            if(d1.g < d2.g)
                return -1;
            return 1;
        }
        if(d1.m < d2.m)
            return -1;
        return 1;
    }
    if(d1.a < d2.a)
        return -1;
    return 1;
}

ora_t getOra(char *s){
    ora_t tmp;
    sscanf(s, "%d:%d", &tmp.h,&tmp.m);
    return tmp;
}

void printOra(ora_t t){
    printf("%d:%d",t.h,t.m);
}

int oracmp(ora_t o1, ora_t o2){
    if(o1.h == o2.h){
        if(o1.m == o2.m)
            return 0;
        if(o1.m < o2.m)
            return -1;
        return 1;
    }
    if(o1.h < o2.h)
        return -1;
    return 1;
}