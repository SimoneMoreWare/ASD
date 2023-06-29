#ifndef PERSONE_H_INCLUDED
#define PERSONE_H_INCLUDED

typedef struct{
    int *E;
    int P;
}Persone;

Persone PERSONEread(FILE *f);
void PERSONEclear(Persone p);

#endif // PERSONE_H_INCLUDED
