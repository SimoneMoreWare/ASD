#include "token.h"

Token TOKENinit(char *val) {
    Token t;

    t = (Token) malloc(sizeof(*t));
    strcpy(t->val, val);

    return t;
}

int TOKENcmp(Token t1, Token t2) {
    return strcmp(t1->val, t2->val);
}