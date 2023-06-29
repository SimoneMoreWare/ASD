#ifndef WORDLUN_H_INCLUDED
#define WORDLUN_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "word.h"

typedef struct {
    int nParole, maxD;
    Word *parole;
}WordLun;

WordLun WORDLUNinit();
void WORDLUNinsertWord(WordLun *wl, Word w);
int WORDLUNgetNumParole(WordLun w);
Word *WORDLUNgetParole(WordLun w);
void WORDLUNfree(WordLun w);
Boolean WORDLUNisThere(WordLun wl, Word w);
void WORDLUNprint(WordLun w, FILE*f);



#endif // WORDLUN_H_INCLUDED
