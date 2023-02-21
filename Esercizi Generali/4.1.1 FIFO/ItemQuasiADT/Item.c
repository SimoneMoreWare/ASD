#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"

int ITEMscan(FILE *fp, Item *dp) {

    if (fp == stdin) {
        printf("Inserisci i dati separati da uno spazio e poi premi invio\n");
        printf("Nell'ordine: str num\n");
    }

    if (fscanf(fp, "%s %d", (*dp).str, &(*dp).num) != 2)
        return 1;

    return 0;
}

void ITEMstore(FILE *fp, Item d) {
		if (fp == NULL) return;
    fprintf(fp, "%s %d\n", d.str, d.num);
}

int ITEMcompare(Item d1, Item d2, int campo) {
    if (campo)
        return d1.num - d2.num;
    else {
        return strcmp(d1.str, d2.str);
    }
}

void ITEMfree(Item dato) {
    return;
}
