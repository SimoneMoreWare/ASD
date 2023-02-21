/*   st.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:45:42
*/
#include "st.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "st.h"


struct hashtable{
    int n,max;
    point *v;
};

ST STinit(int max){
    ST table;
    table = malloc(sizeof(*table));
    table->max = max;
    table->n = 0;
    table->v = malloc(max* sizeof(point));
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

point STgetbyindex(ST table, int index){
    return table->v[index];
}

void STprint(ST table){
    int i;
    for(i=0; i<table->n; i++)
        printf("%2d | %10s\n",i,table->v[i].nome);
    printf("\n\n");
}

int STinsert(ST table, point x){
    if(table->n == table->max){
        return -1;
    }
    table->v[table->n++] = strdup(x);
    return 1;
}
