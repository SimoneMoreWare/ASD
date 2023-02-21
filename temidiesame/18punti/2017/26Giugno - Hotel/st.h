/*   st.h
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:43:53
*/
#ifndef ST_H
#define ST_H

#include "string.h"

typedef struct{
    char *id;
    int arrivo;
    int pernottamenti;
}prenotazione;

typedef struct hashtable *ST;

ST STinit(int max);
void STfree(ST table);
int getN(ST table);
int STsearchbyname(ST table, char *x);
void STprint(ST table);
int STinsert(ST table, prenotazione x);
prenotazione STgetbyindex(ST table, int index);
prenotazione itemCreate(char *id, int ar, int per);
#endif
