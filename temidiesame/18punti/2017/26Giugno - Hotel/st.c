/*   st.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:43:51
*/
#include "st.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct hashtable{
    int n,max;
    prenotazione *v;
};

prenotazione itemCreate(char *id, int ar, int per){
    prenotazione t;
    t.id = strdup(id);
    t.arrivo = ar;
    t.pernottamenti = per;
    return t;
}

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

int STsearchbyname(ST table, char *x){
    int i;
    for(i=0; i<table->n; i++){
        if(strcmp(table->v[i].id,x) == 0)
            return i;
    }
    return -1;
}

prenotazione STgetbyindex(ST table, int index){
    return table->v[index];
}

void STprint(ST table){
    int i;
    for(i=0; i<table->n; i++)
        printf("%2d | %16s| %d | %d\n",i,table->v[i].id,table->v[i].arrivo, table->v[i].pernottamenti);
    printf("\n\n");
}

int STinsert(ST table, prenotazione x){
    if(table->n == table->max){
        table->max = 2*table->max;
        table->v = realloc(table->v, table->max* sizeof(char*));
    }
    table->v[table->n].id = strdup(x.id);
    table->v[table->n].arrivo = x.arrivo;
    table->v[table->n].pernottamenti = x.pernottamenti;
    table->n++;
    return 1;
}

int getN(ST table){
    return table->n;
}