/*   st.h
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:47:22
*/
#ifndef ST_H
#define ST_H

typedef struct hashtable *ST;

ST STinit(int n);
void STfree(ST table);
int STsearchbyname(ST table, char *key);
void STprint(ST table);
int STinsert(ST table, char *x);
char *STgetbyindex(ST table, int index);
int STgetN(ST table);
#endif
