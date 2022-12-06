//
// Created by simone on 06/12/22.
//

#include "inv.h"

void stat_read(FILE *fp, stat_t *statp){
    fscanf(fp,"%d %d %d %d %d %d",
           &(statp->hp),
           &(statp->mp),
           &(statp->atk),
           &(statp->def),
           &(statp->mag),
           &(statp->spr));
}

void inv_read(FILE *fp, inv_t *invp){
    fscanf(fp,"%s %s",
           invp->nome,
           invp->tipo);

    stat_read(fp,&(invp->stat));
}

void stat_print(FILE *fp, stat_t *statp, int soglia){
    fprintf(fp,"%d %d %d %d %d %d",
           (statp->hp),
           (statp->mp),
           (statp->atk),
           (statp->def),
           (statp->mag),
           (statp->spr));
}

void inv_print(FILE *fp, inv_t *invp){
    fprintf(fp,"%s %s\n",
           invp->nome,
           invp->tipo);
    stat_print(fp,&(invp->stat),1);
}

stat_t inv_getStat(inv_t *invp) {
    return invp->stat;
}
