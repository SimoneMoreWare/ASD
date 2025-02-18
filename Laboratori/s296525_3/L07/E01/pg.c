#include "pg.h"

/* lettura e scrittura su file */
int pg_read(FILE *fp, pg_t *pgp) {
    if(fscanf(fp, "%s %s %s", pgp->cod, pgp->nome, pgp->classe) == 3) {
        stat_read(fp, &(pgp->b_stat));
        stat_void(&(pgp->eq_stat));
        pgp->equip = equipArray_init();
        return 1;
    }
    return 0;
}

/* non essendo struct dinamica, pulisce chiamando il distruttore di equipArray */
void pg_clean(pg_t *pgp) {
    equipArray_free(pgp->equip);
    free(pgp);
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray) {
    fprintf(fp, "%s %s %s ", pgp->cod, pgp->nome, pgp->classe);
    stat_print(fp, &(pgp->b_stat), MIN_STAT);
    stat_print(fp, &(pgp->eq_stat), MIN_STAT);
    equipArray_print(fp, pgp->equip, invArray);
    fprintf(fp, "\n");
}

/* modifica personaggio aggiungendo/togliendo un equipaggiamento selezionato da inventario:
di fatto e' sufficiente chiamare l'opportuna funzione dal modulo equipArray */
void pg_updateEquip(pg_t *pgp, invArray_t invArray) {
    int i, equipped;
    stat_t tmp;
    equipArray_update(pgp->equip, invArray);
    stat_void(&(pgp->eq_stat));
    for(i = 0; i < EQUIP_SLOT; i++) {
        equipped = equipArray_getEquipByIndex(pgp->equip, i);
        if(equipped != -1) {
            tmp = inv_getStat(invArray_getByIndex(invArray, equipped));
            pgp->eq_stat.hp += tmp.hp;
            pgp->eq_stat.mp += tmp.mp;
            pgp->eq_stat.atk += tmp.atk;
            pgp->eq_stat.def += tmp.def;
            pgp->eq_stat.mag += tmp.mag;
            pgp->eq_stat.spr += tmp.spr;
        }
    }
}
