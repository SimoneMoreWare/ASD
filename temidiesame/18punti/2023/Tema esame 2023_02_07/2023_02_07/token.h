#ifndef TOKEN_H
#define TOKEN_H

#define TOKEN_DIM 2+1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct token_t {
    char val[TOKEN_DIM];
} *Token;

Token TOKENinit(char *val);
int TOKENcmp(Token t1, Token t2);

#endif