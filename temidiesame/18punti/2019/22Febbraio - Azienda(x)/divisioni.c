/*   divisioni.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:47:07
*/
#include "divisioni.h"
#include "dipendente.h"
#include <stdlib.h>
#include <string.h>
#include "stdio.h"

struct divisioni{
    char *sigla;
    dipendente_t *v;
    int n, max;
    int richieste[4][3];
};

divisioni_t divisioniNEW(char *sigla, int MAX){
    divisioni_t t;
    t = malloc(sizeof(*t));
    t->sigla = strdup(sigla);
    t->max = MAX;
    return t;
}

void divisioniFree(divisioni_t t){
    free(t->v);
    free(t->sigla);
    free(t);
}

divisioni_t divisioniScan(FILE *in, int MAX){
    divisioni_t t;
    char cod[11];
    int i,tot=0;
    fscanf(in,"%s\n", cod);
    t = divisioniNEW(cod, MAX);
    for(i=0; i<4; i++){
        fscanf(in, "%d %d %d\n", &t->richieste[i][0],&t->richieste[i][1],&t->richieste[i][2]);
        tot += t->richieste[i][0];
    }
    t->n = 0;
    t->max = 2*tot;
    t->v = malloc(2*tot*sizeof(dipendente_t));
    return t;
}

void divisioniInsertDipendente(divisioni_t t, dipendente_t dip){
    t->v[t->n++] = dip;
    return;
}

void divisioniStore(FILE *out, divisioni_t t){
    int i;
    for(i=0; i<t->n; i++){
        fprintf(out, "%d %c %s", t->v[i].matr, t->v[i].tipo, t->sigla);
    }
}