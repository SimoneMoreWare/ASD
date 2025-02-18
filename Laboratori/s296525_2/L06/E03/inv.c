#ifndef mod_inv
    #define mod_inv
    #include "inv.h"
#endif

item* ITEMget(char *name, char *type, int hp, int mp, int atk, int def, int mag, int spr) {
    item *item_get = (item*) malloc(sizeof(item));
    item_get->stat = (stats*) malloc(sizeof(stats)); 
    
    item_get->usingItem = 0;
    strcpy(item_get->name, name);
    strcpy(item_get->type, type);
    
    item_get->stat = STATSget(hp, mp, atk, def, mag, spr);

    return item_get;
}

item* ITEMsearch(tabInv inv, char *name) {
    int i;

    for(i = 0; i < inv.nInv; i++) {
        if(strcmp(inv.vettInv[i]->name, name) == 0)
            return inv.vettInv[i];
    }

    return NULL;
}

void ITEMprint(item it) {
    printf("Utilizzato: %d\n"
           "Nome: %s\n"
           "Tipologia: %s\n",
            it.usingItem,
            it.name,
            it.type
           );
    STATSprint(*(it.stat));
}

void ITEMfree(item* it) {
    free(it);
}

tabInv* TABINVinit() {
    tabInv* inv = (tabInv*) malloc(sizeof(tabInv));
    FILE* file;
    int i, hp, mp, atk, def, mag, spr;
    char name[MAX_LENGTH_ITEM], type[MAX_LENGTH_ITEM];

    if((file = fopen(fileNameINV, "r")) == NULL) {
        printf("Non è stato possibile aprire il file %s.", fileNameINV);
        return NULL;
    }

    fscanf(file, "%d", &(inv->maxInv));
    inv->vettInv = (item**) malloc(inv->maxInv*sizeof(item*));
    inv->nInv = 0;
    for(i = 0; i < inv->maxInv; i++) {
        fscanf(file, "%s %s %d %d %d %d %d %d", 
               name, type, &hp, &mp, &atk, &def, &mag, &spr);
        inv->vettInv[i] = ITEMget(name, type, hp, mp, atk, def, mag, spr);
        inv->nInv++;
    }

    fclose(file);

    return inv;
}

void TABINVfree(tabInv* tab) {
    int i;
    
    for(i = 0; i < tab->maxInv; i++) {
        free(tab->vettInv[i]);
    }
    free(tab->vettInv);
    free(tab);
}
