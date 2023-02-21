/*   dipendente.h
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:47:06
*/
#ifndef DIPENDENTE_H
#define DIPENDENTE_H

typedef struct{
    int matr;
    char nome[21], cognome[21];
    int o, a, t, i;
    char tipo;
}dipendente_t;
#endif
