/*   st.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:42:43
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "st.h"


struct hashtable{
    int n,max;
    char  **v;
};

ST STinit(int max){
    ST table;
    table = malloc(sizeof(*table));
    table->max = max;
    table->n = 0;
    table->v = malloc(max* sizeof(char*));
    return table;
}

void STfree(ST table){
    int i;
    free(table->v);
    free(table);
}

int STsearchbyname(ST table, char *key){
    int i;
    for(i=0; i<table->n; i++){
        if(strcmp(table->v[i],key) == 0)
            return i;
    }
    return -1;
}

char *STgetbyindex(ST table, int index){
    return table->v[index];
}

void STprint(ST table){
    int i;
    for(i=0; i<table->n; i++)
        printf("%2d | %10s\n",i,table->v[i]);
    printf("\n\n");
}

int STinsert(ST table, char *x) {
    if (table->n == table->max) {
        table->v = realloc(table->v, 2 * table->max * sizeof(char *));
        table->max = 2 * table->max;
    }
    table->v[table->n++] = strdup(x);
    return 1;
}

int STgetN(ST table){
    return table->n;
}