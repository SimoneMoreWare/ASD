#ifndef TIME_H
#define TIME_H

typedef struct{
    int a,m,g;
}data_t;

typedef struct{
    int h,m;
}ora_t;

data_t getData(char *s);
void printData(data_t t);
int datacmp(data_t d1, data_t d2);

ora_t getOra(char *s);
void printOra(ora_t t);
int oracmp(ora_t o1, ora_t o2);

#endif
