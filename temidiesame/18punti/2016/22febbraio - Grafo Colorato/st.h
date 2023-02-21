/*   st.h
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:43:12
*/
#ifndef ST_H
#define ST_H

#include "string.h"

typedef struct{
    char *id;
    char c; //R o N
}Item;

Item ItemCreate(char *id, char *colore);

typedef struct hashtable *ST;

ST STinit(int max);
void STfree(ST table);
int getN(ST table);
int STsearchbyname(ST table, char *x);
void STprint(ST table);
int STinsert(ST table, Item x);
Item STgetbyindex(ST table, int index);
char STgetColor(ST table, int index);
#endif
