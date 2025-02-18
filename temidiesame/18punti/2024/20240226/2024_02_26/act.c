#include "act.h"

typedef struct activity { 
    char nome[MAX_LEN];
    int t_i, t_f;
    int val;
    int precedenti[MAX_VINC];
    int prec;
} *Activity;

typedef struct activities {
    int NA, NP;
    Activity *a;
} *ACT;

/* Ottieni una singola attività */
static Activity ACTIVITYfile(FILE *file) {
    Activity att;
    char nome[MAX_LEN];
    int t_i, t_f, val;

    att = (Activity) malloc(sizeof(*att));
    
    fscanf(file, "%s %d %d %d", nome, t_i, t_f, val);
    
    strcpy(att->nome, nome);
    att->t_i = t_i;
    att->t_f = t_f;
    att->val = val;

    return att;
}

/* Ottieni l'indice dell'attività identificata dal nome */
static int ACTIVITYindex(ACT atts, char *s) {
    int i;

    for (i = 0; i < atts->NA; i++)
        if (strcmp(atts->a[i]->nome, s) == 0)
            return i;
    
    return -1;
}

/* Ottieni i vincoli di precedenza presenti nel file */
static ACT ACTIVITYfileVincoli(FILE *file, ACT atts) {
    int i, j, index;
    char s[MAX_LEN];

    fscanf(file, "%s", s);
    index = ACTIVITYindex(atts, s);

    if (index == -1)
        return NULL;

    i = 0;
    while (fscanf(file, "%s", s) == 1) {
        j = ACTIVITYindex(atts, s);
        atts->a[index]->precedenti[i] = j;
        i++;
    }

    for ( ; i < 2; i++)
        atts->a[index]->precedenti[i] = -1;

    return atts;
}

/* Leggi l'intero file contenente le attività */
ACT activityRead(FILE *file) {
    int i;
    ACT atts;

    atts = (ACT) malloc(sizeof(*atts));
    fscanf(file, "%d %d", &(atts->NA), &(atts->NP));
    
    /* Per le attività */
    for (i = 0; i < atts->NA; i++)
        atts->a[i] = ACTIVITYfile(file);
    
    /* Per i vincoli */
    for (i = 0; i < atts->NP; i++)
        atts = ACTIVITYfileVincoli(file, atts);

    return atts;
}

/* Controlla che le precedenze siano rispettate */
static int checkUntilIndex(ACT a, int index, char **selected, int curr) {
    int i, j, k;
    int *isIn;

    isIn = (int*) calloc(MAX_VINC, sizeof(int));
    for (i = 0; i < curr; i++) {
        k = ACTIVITYindex(a, selected[i]);
        if (a->a[k]->t_f >= a->a[index]->t_i && 
            a->a[k]->t_i <= a->a[index]->t_f)
            return 0;

        for (j = 0; j < MAX_VINC && a->a[index]->precedenti[j] != -1; j++) {
            if (a->a[index]->precedenti[j] == k)
                isIn[j] = 1;
        }
    }

    for (i = 0; i < MAX_VINC; i++)
        if (isIn[i] == 0)
            return 0;

    return 1;
} 

int checkSelection(ACT a, char **selected, int nsel) {
    int i, j;

    for (i = 0; i < nsel; i++) {
        /* Trova l'attività che si vuole selezionare */
        j = ACTIVITYindex(a, selected[i]);
        if (j == -1)
            return 0;

        /* Controlla che siano rispettati i vincoli */
        if (checkUntilIndex(a, j, selected, i) == 0)
            return 0;
    }

    return 1;
}

void comb_sempl(int pos, ACT atts, char **sol, char **best_sol, int n, int *best_n, int val, int *best_val, int start) {
    int i;

    if (pos >= atts->NA) {
        if (checkSelection(atts, sol, n) && val > *best_val) {
            *best_n = n;
            *best_val = val;
            for (i = 0; i < n; i++) {
                strcpy(best_sol[i], sol[i]);
            }
        }
        return;
    }
    for (i = start; i < n; i++) {
        sol[i] = atts->a[pos]->nome;
        comb_sempl(pos+1, atts, sol, best_sol, n, best_n, val + atts->a[pos]->val, best_val, start+1);
    }
    return;
}

// Order acts by starting time
void sortACTS(ACT acts, int n) {
    acts->a = QuickSortR(acts->a, 0, n);
}

char **bestSelection(ACT atts, int *n) {
    char **sol, **best_sol;
    sol = (char**) malloc(atts->NA * sizeof(char*));
    best_sol = (char**) malloc(atts->NA * sizeof(char*));

    sortACTS(atts, n);

    comb_sempl(0, atts, sol, best_sol, atts->NA, 0, 0, 0, 0);

    return best_sol;
}