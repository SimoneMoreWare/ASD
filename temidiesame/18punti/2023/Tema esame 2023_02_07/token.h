#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct{
   char car[3];
}Token;

typedef enum{VERO, FALSO}Boolean;

Token TOKENread(FILE *f);
int TOKENcompare(Token t1, Token t2);
Boolean TOKENisSubToken(Token *t1, int dim1, Token *t2, int dim2);
void TOKENprint(Token t, FILE *f);

#endif // TOKEN_H_INCLUDED
