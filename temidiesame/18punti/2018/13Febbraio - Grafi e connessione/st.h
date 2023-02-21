/*   st.h
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:45:44
*/
#ifndef ST_H
#define ST_H

#include "point.h"

typedef struct hashtable *ST;

ST STinit(int n);
void STfree(ST table);
int STsearchbyname(ST table, char *x);
void STprint(ST table);
int STinsert(ST table, point x);
point STgetbyindex(ST table, int index);
void STsort(ST table);
#endif
