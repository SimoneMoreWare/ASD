/*   st.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:43:18
*/
#include "st.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct hashtable{
    int n,max;
    Item *v;
};

Item ItemCreate(char *id, int pop, int dist){
    Item t;
    t.name = strdup(id);
    t.pop = pop;
    t.dist = dist;
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
        if(strcmp(table->v[i].name,x) == 0)
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
        printf("%2d | %15s| %3d | %3d\n",i,table->v[i].name,table->v[i].pop, table->v[i].dist);
    printf("\n\n");
}

int STinsert(ST table, Item x){
    if(table->n == table->max){
        return -1;
    }
    table->v[table->n].name = strdup(x.name);
    table->v[table->n].pop = x.pop;
    table->v[table->n].dist = x.dist;
    table->n++;
    return 1;
}
