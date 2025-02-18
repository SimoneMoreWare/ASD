#define mod_stats 
#include "stats.h"

stats* STATSget(int hp, int mp, int atk, int def, int mag, int spr) {
    stats* stat_insert = (stats*) malloc(sizeof(stats));
    
    stat_insert->hp = hp;
    stat_insert->mp = mp;
    stat_insert->atk = atk;
    stat_insert->def = def;
    stat_insert->mag = mag;
    stat_insert->spr = spr;

    return stat_insert;
}

stats* STATScalc(stats* stat1, stats* stat2) {
    stats* calc = (stats*) malloc(sizeof(stats));
    
    calc->hp = stat1->hp + stat2->hp;
    if(calc->hp < 0)
        calc->hp = 0;
    
    calc->mp = stat1->mp + stat2->mp;
    if(calc->mp < 0)
        calc->mp = 0;
    
    calc->atk = stat1->atk + stat2->atk;
    if(calc->atk < 0)
        calc->atk = 0;
    
    calc->def = stat1->def + stat2->def;
    if(calc->def < 0)
        calc->def = 0;
    
    calc->mag = stat1->mag + stat2->mag;
    if(calc->mag < 0)
        calc->mag = 0;
    
    calc->spr = stat1->spr + stat2->spr;
    if(calc->spr < 0)
        calc->spr = 0;

    return calc;
}

void STATSprint(stats stat) {
    printf("HP: %d \n"
           "MP: %d \n"
           "ATK: %d \n"
           "DEF: %d \n"
           "MAG: %d \n"
           "SPR: %d \n",
           stat.hp, stat.mp, stat.atk, stat.def, stat.mag, stat.spr);
}

void STATSfree(stats *stat) {
    free(stat);
}