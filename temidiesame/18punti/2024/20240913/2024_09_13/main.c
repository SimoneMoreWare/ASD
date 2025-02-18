#include "ELENCO.h"
#include "DISTMATR.h"
#include "SEDI.h"
#include "SERVIZI.h"

void caricaDati(FILE* file, ELENCO *e, DISTMATR *d) {
    *e = ELENCOfile(file);
    *d = DISTMATRinit(ELENCOgetN(*e));
    *d = DISTMATRfile(file, *d);
}

int checkSedi(DISTMATR d, int MAXD, int MINS, SEDI s) {
    int i, j, flag, n;
    if ((SEDIgetN(s) - SEDIgetNumS(s)) < MINS)
        return 0;
 
    for (i = 0; i < SEDIgetN(s); i++) {
        if (SEDIisSede(s, i) == 0) {
            flag = 0;
            for (j = 0; j < SEDIgetN(s) && flag == 0; j++)
                if (i != j && SEDIisSede(s, j) == 1 && DISTMATRgetVal(d, i, j) <= MAXD) {
                    flag = 1;
                    break;
                }
            if (flag == 0)
                return 0;
        }

        if (SEDIisSede(s, i) == 1) {
            n = 0;
            for (j = 0; j < SEDIgetN(s); j++)
                if (i != j && SEDIisSede(s, j) == 0 && DISTMATRgetVal(d, i, j) <= MAXD)
                    n++;
            if (n < MINS)
                return 0;
        }
    }

    // eliminato secondo ciclo, si può fare nel primo

    return 1;
}

int main(void) {
    ELENCO e;
    DISTMATR d;
    SEDI s;
    SERVIZI se;
    FILE* file;

    // inserimento dati
    file = fopen("data.txt", "r");
    caricaDati(file, &e, &d);
    fclose(file);

    // test delle sedi
    file = fopen("testSedi.txt", "r");
    s = SEDIfile(file);
    fclose(file);

    printf("TEST SEDI #1\n");
    printf("EXPECTED = %d\n", 1);
    printf("OBTAINED = %d\n", checkSedi(d, 4, 2, s));

    printf("\nTEST SEDI #2\n");
    printf("EXPECTED = %d\n", 0);
    printf("OBTAINED = %d\n", checkSedi(d, 4, 3, s));

    // test dei servizi
    file = fopen("testServizi1.txt", "r");
    se = SERVIZIfile(file);
    fclose(file);

    printf("\nTEST SERVIZI #1\n");
    printf("EXPECTED = %d\n", 1);
    printf("OBTAINED = %d\n", checkPart(se, d, 4, 2));

    file = fopen("testServizi2.txt", "r");
    se = SERVIZIfile(file);
    fclose(file);

    printf("\nTEST SERVIZI #2\n");
    printf("EXPECTED = %d\n", 0);
    printf("OBTAINED = %d\n", checkPart(se, d, 4, 2));

    return 0;
}