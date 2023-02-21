/*   st.h
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:43:20
*/
#ifndef ST_H
#define ST_H

#include "string.h"

typedef struct{
    char *name;
    int pop;
    int dist;
}Item;

Item ItemCreate(char *id, int pop, int dist);

typedef struct hashtable *ST;

ST STinit(int n);
void STfree(ST table);
int STsearchbyname(ST table, char *x);
void STprint(ST table);
int STinsert(ST table, Item x);
Item STgetbyindex(ST table, int index);
void STsort(ST table);
#endif
