#include <stdio.h>
#include <stdlib.h>

typedef struct stats_t {
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
} stats;

stats* STATSget(int hp, int mp, int atk, int def, int mag, int spr);

stats* STATScalc(stats* stat1, stats* stat2);

void STATSprint(stats stat);

void STATSfree(stats *stat);