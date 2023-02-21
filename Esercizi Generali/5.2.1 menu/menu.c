#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLEN 50

typedef struct portata_ {
    int np;
    char **piatti;
} portata;

portata *leggiPortate(FILE *in, int *n) {
    portata *p = NULL;
    int np = -1, i, j, cnt = 0;
    char piatto[MAXLEN];
    printf("sono in leggiPortate\n");
    while(fscanf(in, "%d", &np) == 1) {
        printf("np=%d\n", np);
        for (i=0; i<np; i++)
           fscanf(in, "%*s");
        cnt++;
    }
    rewind(in);
    printf("cnt =%d\n", cnt);
    p = calloc(cnt, sizeof(portata));
    if(p == NULL)
      exit(-1);

    for(i=0; i<cnt; i++) {
        fscanf(in, "%d\n", &p[i].np);
        p[i].piatti = calloc(p[i].np, sizeof(char*));
        if (p[i].piatti == NULL)
          exit(-1);
        for(j=0; j<p[i].np; j++) {
            fscanf(in, "%s", piatto);
            p[i].piatti[j] = strdup(piatto);
            if (p[i].piatti[j] == NULL)
              exit(-1);
        }
    }
    *n = cnt;
    return p;
}

void stampa(portata *p, int n, int *menu) {
    int i;
    for(i=0;i<n;i++) {
        printf("%s ", p[i].piatti[menu[i]]);
    }
    printf("\n");
}

int generaMenuR(portata *p, int pos, int n, int *menu, int cnt) {
    int i;
    if (pos >= n) {
        stampa(p, n, menu);
        return cnt+1;
    }
    for(i=0;i<p[pos].np;i++) {
        menu[pos] = i;
        cnt =generaMenuR(p, pos+1, n, menu, cnt);
    }
    return cnt;
}

void generaMenu(portata *p, int n) {
    int *menu, cnt;
    menu = calloc(n, sizeof(int));
    if (menu == NULL)
      exit(-1);
    cnt = generaMenuR(p, 0, n, menu,0);
    free(menu);
    printf("Ci sono %d possibili menu\n", cnt);
}

int main(int argc, char **argv) {

    int n = 0,i,j;
    portata *p;
    FILE *in;

    in = fopen(argv[1], "r");
    if (in == NULL)
      exit(-1);

    p = leggiPortate(in, &n);
    printf("num. portate %d\n", n);
    generaMenu(p, n);
    for(i=0; i<n; i++) {
      for(j=0; j<p[i].np; j++) {
        free(p[i].piatti[j]);
      }
      free(p[i].piatti);
    }
    free(p);
    fclose(in);
    return 0;
}
