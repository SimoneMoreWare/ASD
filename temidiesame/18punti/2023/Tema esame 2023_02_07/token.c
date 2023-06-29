#include "token.h"
#include <string.h>

Token TOKENread(FILE *f){
    Token t;
    char car[3];
    fscanf(f, "%s", car);
    strcpy(t.car, car);
    return t;
}


int TOKENcompare(Token t1, Token t2){
   return strcmp(t1.car, t2.car);
}


Boolean TOKENisSubToken(Token *t1, int dim1, Token *t2, int dim2){
    char *str1, *str2;
    int i;

    str1=(char*)malloc((1+(dim1*2))*sizeof(char));
    if(str1==NULL) exit(EXIT_FAILURE);

    str2=(char*)malloc((1+(dim2*2))*sizeof(char));
    if(str2==NULL) exit(EXIT_FAILURE);

    strcpy(str1, "");
    strcpy(str2, "");
    for(i=0; i<dim1; i++){
       strcat(str1, t1[i].car);
    }

    for(i=0; i<dim2; i++){
       strcat(str2, t2[i].car);
    }

    if(strstr(str1, str2)==NULL)
       return FALSO;
    return VERO;
}


void TOKENprint(Token t, FILE *f){
    fprintf(f, "%s", t.car);
    return;
}
