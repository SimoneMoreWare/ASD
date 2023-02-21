/*   st.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:46:45
*/
#include "st.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct hashtable{
    int n,max;
    Item *v;
};

Item ItemCreate(char *id){
    Item t;
    t.id = strdup(id);
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
        printf("%2d | %15s\n",i,table->v[i].id);
    printf("\n\n");
}

int STinsert(ST table, Item x){
    if(table->n == table->max){
        return -1;
    }
    table->v[table->n] = x;
    return 1;
}

int getN(ST table){
    return table->n;
}