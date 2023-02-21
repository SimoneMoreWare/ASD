#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"

struct item {
    char *str;
    int num;
};

int ITEMscan(FILE *fp, Item *dp) {

    char str[MAXC];
    int num;

    if (fp == stdin) {
        printf("Inserisci i dati separati da uno spazio e poi premi invio\n");
        printf("Nell'ordine: str num\n");
    }

    if (fscanf(fp, "%s %d", str, &num) != 2)
        return 1;

    *dp = ITEMnew(str, num);
    if (*dp == NULL) exit(-1);
    return 0;
}

void ITEMstore(FILE *fp, Item d) {
		if (fp == NULL) return;
    fprintf(fp, "%s %d\n", d->str, d->num);
}

int ITEMcompare(Item d1, Item d2, int campo) {
    if (campo)
        return d1->num - d2->num;
    else {
        return strcmp(d1->str, d2->str);
    }
}

void ITEMfree(Item dato) {
    if (dato == NULL) return;
    if (dato->str != NULL) free(dato->str);
    free(dato);
}

Item ITEMnew(char *str, int num) {
    Item tmp = (Item) malloc(sizeof(struct item));
    if (tmp != NULL) {
        tmp->str = strdup(str);
        if (tmp->str == NULL) exit(-1);
        tmp->num = num;
    }
    return tmp;
}
