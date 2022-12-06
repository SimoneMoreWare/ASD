//
// Created by simone on 06/12/22.
//

#include "pg.h"

int pg_read(FILE *fp, pg_t *pgp){
    int ret;

    ret = fscanf(fp,"%s %s %s",
                 pgp->cod,
                 pgp->nome,
                 pgp->classe);

    stat_read(fp,&(pgp->b_stat));

    pgp->eq_stat = pgp->b_stat;

    // se non ho letto non alloco
    if(ret == 3) pgp->equip = equipArray_init();


    return (ret == 3);
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray){
    printf("%s %s %s\n",
           pgp->cod,
           pgp->nome,
           pgp->classe);
    stat_print(fp,&(pgp->eq_stat),1);
    equipArray_print(fp,pgp->equip,invArray);
}

void pg_clean(pg_t *pgp) {
    equipArray_free(pgp->equip);
}

void pg_updateEquip(pg_t *pgp, invArray_t invArray) {
    equipArray_update(pgp->equip,invArray);
    pg_updateStat(pgp,invArray);
}

void pg_updateStat(pg_t *pgp, invArray_t invArray) {
    stat_t stat = equipArray_getLastStat(pgp->equip,invArray);

    pgp->eq_stat.hp += stat.hp;
    pgp->eq_stat.mp += stat.mp;
    pgp->eq_stat.atk += stat.atk;
    pgp->eq_stat.def += stat.def;
    pgp->eq_stat.mag += stat.mag;
    pgp->eq_stat.spr += stat.spr;
}
