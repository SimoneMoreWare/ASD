#ifndef mod_pg
    #define mod_pg
    #include "pg.h"
#endif

int PGcodecheck(char *code) {
    int i;

    if(strlen(code) == MAX_LENGTH_CODE)
        if(code[0] == 'P' && code[1] == 'G')
            for(i = 2; i < MAX_LENGTH_CODE; i++)
                if(code[i] < '0' || code[i] > '9')
                    return 0;
    
    return 1;
}

link PGget(char *code, char *name, char *pgClass, int hp, int mp, int atk, int def, int mag, int spr) {
    if(!PGcodecheck(code))
        return NULL;
    
    link pg_insert = (link) malloc(sizeof(pg));
    pg_insert->stat = (stats*) malloc(sizeof(stats));

    strcpy(pg_insert->code, code);
    strcpy(pg_insert->name, name);
    strcpy(pg_insert->pgClass, pgClass);
    
    pg_insert->equip = (tabEquip*) malloc(sizeof(tabEquip));
    pg_insert->equip->usingPG = 0;
    pg_insert->equip->vettEq = (item**) malloc(MAX_ITEMS*sizeof(item*));
    
    pg_insert->stat = STATSget(hp, mp, atk, def, mag, spr);

    pg_insert->next = NULL;

    return pg_insert;
}

void PGfree(link freePG) {
    STATSfree(freePG->stat);
    free(freePG->equip->vettEq);
    free(freePG->equip);
    free(freePG);
}

tabPg* TABPGinit() {
    tabPg* tabPg_insert = (tabPg*) malloc(sizeof(tabPg));
    tabPg_insert->headPg = NULL;
    tabPg_insert->nPg = 0;

    FILE *file;
    int hp, mp, atk, def, mag, spr;
    char code[MAX_LENGTH_CODE], name[MAX_LENGTH_PG], pgClass[MAX_LENGTH_PG];
    link insert = NULL, x = NULL, prev;

    if((file = fopen(fileNamePG, "r")) == NULL) {
        printf("Non è stato possibile aprire il file %s.\n", fileNameINV);
        return NULL;
    }

    while(fscanf(file, "%s %s %s %d %d %d %d %d %d", code, name, pgClass, &hp, &mp, &atk, &def, &mag, &spr) == 9) {
        
        if(PGsearch(*tabPg_insert, code) != NULL) {
            printf("Il personaggio con codice %s è già stato inserito.\n", code);
            continue;
        }
        insert = PGget(code, name, pgClass, hp, mp, atk, def, mag, spr);
        
        if(insert != NULL) {
            PGinsert(tabPg_insert, insert);
            if(x == NULL) 
                x = tabPg_insert->headPg;
            else {
                prev = x;
                x = x->next;
            }
            tabPg_insert->nPg++;
        }
    }
    tabPg_insert->tailPg = insert;

    return tabPg_insert;
}

void TABPGfree(tabPg *tab) {
    link x, del;
    
    while(tab->headPg != NULL) {
        del = tab->headPg;
        tab->headPg = tab->headPg->next;
        del->next = NULL;
        PGfree(del);
    }
}

void PGinsert(tabPg *tab, link insert) {
    link x;
    if(tab->headPg == NULL) {
        tab->headPg = insert;
    } else {
        for(x = tab->headPg; x->next != NULL; x = x->next);
        x->next = insert;
    }
}

link PGsearch(tabPg tab, char *code) {
    link x;
    
    if(PGcodecheck(code)) {
        for(x = tab.headPg; x != NULL; x = x->next) {
            if(strcmp(x->code, code) == 0) {
                return x;
            }
        }
    }
    return NULL;
}

void PGdelete(tabPg *tab, char *code) {
    link del = NULL, x, prev;
    
    for(x = tab->headPg, prev = NULL; x != NULL; prev = x, x = x->next) {
        if(strcmp(x->code, code) == 0) {
            del = x;
            break;
        }
    }

    if(del != NULL) {
        if(prev != NULL)
            prev->next = del->next;
        else
            tab->headPg = del->next;
        if(del == tab->tailPg)
            tab->tailPg = prev;
        
        PGfree(del);
        tab->nPg--;
        return;
    }

    printf("Il personaggio con codice %s non e' stato trovato.\n", code);
}

void PGprint(tabPg tab, char *code) {
    link x;
    stats* calc;
    int i;
    if((x = PGsearch(tab, code)) != NULL) {
        calc = x->stat;

        printf("\nCodice: %s\n"
               "Nome: %s\n"
               "Classe: %s\n",
               x->code, x->name, x->pgClass
               );
        if(x->equip->usingPG != 0) {
            for(i = 0; i < x->equip->usingPG; i++) {
                printf("Item %d\n", i+1);
                ITEMprint(*(x->equip->vettEq[i]));
                calc = STATScalc(calc, x->equip->vettEq[i]->stat);
                printf("\n");
            }
        } else {
            printf("Il personaggio non ha oggetti.\n");
        }
        STATSprint(*calc);
        printf("\n");
    }
}

void PGgainItem(tabPg *tab, char *code, tabInv inv, char *itemName) {
    link x = PGsearch(*tab, code);
    item* y = ITEMsearch(inv, itemName);

    if(y->usingItem) {
        printf("L'oggetto è già in uso da un personaggio.\n");
    } else if(x->equip->usingPG < 8) {
        x->equip->vettEq[x->equip->usingPG] = y;
        x->equip->usingPG++;
        y->usingItem = 1;
    } else {
        printf("Il personaggio ha il numero massimo di oggetti.\n");
    }
}

void PGremoveItem(tabPg *tab, char *code, tabInv inv, char *itemName) {
    link x = PGsearch(*tab, code);
    item* y = ITEMsearch(inv, itemName);
    int i;

    if(x->equip->usingPG > 0) {
        for(i = 0; i < x->equip->usingPG; i++) {
            if(strcmp(x->equip->vettEq[i]->name, itemName) == 0) {
                x->equip->vettEq[i] = NULL;
                x->equip->usingPG--;
                y->usingItem = 0;
            }
        }
    } else {
        printf("Il personaggio ha il numero massimo di oggetti.\n");
    }
}
