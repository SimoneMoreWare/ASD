/*   st.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:43:10
*/
#include "st.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct hashtable{
    int n,max;
    Item *v;
};

Item ItemCreate(char *id, char *colore){
    Item t;
    t.id = strdup(id);
    if(strcmp(colore,"ROSSO"))
        t.c = 'R';
    else
        t.c = 'N';
    return t;
}

ST STinit(int max){
    ST table;
    table = malloc(sizeof(*table));
    table->max = max;
    table->n = 0;
    table->v = malloc(max* sizeof(Item));
    return table;
}

void STfree(ST table){
    int i;
    free(table->v);
    free(table);
}

int STsearchbyname(ST table, char *x){
    int i;
    for(i=0; i<table->n; i++){
        if(strcmp(table->v[i].id,x) == 0)
            return i;
    }
    return -1;
}

Item STgetbyindex(ST table, int index){
    return table->v[index];
}

void STprint(ST table){
    int i;
    for(i=0; i<table->n; i++)
        printf("%2d | %15s| %c\n",i,table->v[i].id,table->v[i].c);
    printf("\n\n");
}

int STinsert(ST table, Item x){
    if(table->n == table->max){
        realloc(table->v,2*table->max* sizeof(Item));
    }
    table->v[table->n] = x;
    return 1;
}

char STgetColor(ST table, int index){
    return table->v[index].c;
}

int getN(ST table){
    return table->n;
}