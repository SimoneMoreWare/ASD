#ifndef INCARICHI_H_INCLUDED
#define INCARICHI_H_INCLUDED

typedef struct{
    int *D;
    int T;
}Incarichi;

Incarichi INCARICHIread(FILE *f);
void INCARICHIclear(Incarichi i);

#endif // INCARICHI_H_INCLUDED
