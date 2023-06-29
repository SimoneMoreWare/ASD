#ifndef SINERGIA_H_INCLUDED
#define SINERGIA_H_INCLUDED

typedef struct{
    int **S;
    int P;
}Sinergia;

Sinergia SINERGIAread(FILE *f, int P);
void SINERGIAclear(Sinergia s);
#endif // SINERGIA_H_INCLUDED
