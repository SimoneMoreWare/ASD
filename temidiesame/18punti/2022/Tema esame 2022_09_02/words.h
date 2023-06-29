#ifndef WORDS_H_INCLUDED
#define WORDS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define CAR 16

typedef struct{
    char parola[CAR];
    int valore;
}Word;

typedef struct{
    Word *parole;
    int nParole;
}Words;


Word WORDread(FILE *f);
void WORDSorder(Words w);
Words WORDScrea(int dim);
Words WORDSread(FILE *f);
void WORDSclear(Words w);

#endif // WORDS_H_INCLUDED
