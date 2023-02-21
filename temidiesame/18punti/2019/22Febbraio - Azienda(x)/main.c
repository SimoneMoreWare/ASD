/*   main.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:47:11
*/
#include <stdio.h>
#include <stdlib.h>

#include "divisioni.h"
#include "dipendente.h"

int main(int argc, char **argv) {
    FILE *in;
    int i, n, D;
    dipendente_t *dipendenti;
    divisioni_t *divisioni;
    in = fopen(argv[1], "r");
    fscanf(in, "%d\n", &n);
    dipendenti = malloc(n* sizeof(dipendente_t));
    for(i=0; i<n; i++)
        fscanf(in, "%d %s %s %d %d %d %d\n", &dipendenti[i].matr, dipendenti[i].nome, dipendenti[i].cognome, &dipendenti[i].o, &dipendenti[i].a, &dipendenti[i].t, &dipendenti[i].i);
    fclose(in);
    in = fopen(argv[2], "r");
    fscanf(in, "%d\n", &D);
    divisioni = malloc(D* sizeof(divisioni_t));
    for(i=0; i<D; i++)
        divisioni[i] = divisioniScan(in, n);
    fclose(in);
    in =  fopen(argv[3], "r");
    for(i=0; i<n; i++){

    }
    fclose(in);
    return 0;
}