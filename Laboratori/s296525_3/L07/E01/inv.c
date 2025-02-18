#include "inv.h"

/* funzioni di input/output delle statistiche */
void stat_read(FILE *fp, stat_t *statp) {
    fscanf(fp, "%d %d %d %d %d %d", 
                &(statp->hp), &(statp->mp), &(statp->atk), 
                &(statp->def), &(statp->mag), &(statp->spr)
    );
}

void stat_print(FILE *fp, stat_t *statp, int soglia) {
    if(statp->hp < soglia)
        fprintf(fp, "%d ", soglia);
    else
        fprintf(fp, "%d ", statp->hp);
    
    if(statp->mp < soglia)
        fprintf(fp, "%d ", soglia);
    else
        fprintf(fp, "%d ", statp->mp);

    if(statp->atk < soglia)
        fprintf(fp, "%d ", soglia);
    else
        fprintf(fp, "%d ", statp->atk);

    if(statp->def < soglia)
        fprintf(fp, "%d ", soglia);
    else
        fprintf(fp, "%d ", statp->def);

    if(statp->mag < soglia)
        fprintf(fp, "%d ", soglia);
    else
        fprintf(fp, "%d ", statp->mag);

    if(statp->spr < soglia)
        fprintf(fp, "%d ", soglia);
    else
        fprintf(fp, "%d ", statp->spr);
}

void stat_free(stat_t *statp) {
    free(statp);
}

void stat_void(stat_t *statp) {
    statp->hp = MIN_STAT;
    statp->mp = MIN_STAT;
    statp->atk = MIN_STAT;
    statp->def = MIN_STAT;
    statp->mag = MIN_STAT;
    statp->spr = MIN_STAT;
}

/* funzioni di input/output di un oggetto dell'inventario */
void inv_read(FILE *fp, inv_t *invp) {
    fscanf(fp, "%s %s", invp->nome, invp->tipo);
    stat_read(fp, &(invp->stat));
}

void inv_print(FILE *fp, inv_t *invp) {
    fprintf(fp, "%s %s ", invp->nome, invp->tipo);
    stat_print(fp, &(invp->stat), MIN_STAT);
    fprintf(fp, "\n");
}

void inv_free(inv_t *invp) {
    stat_free(&(invp->stat));
    free(invp);
}

/* ritorna il campo stat di un oggetto dell'inventario */
stat_t inv_getStat(inv_t *invp) {
    return invp->stat;
}
