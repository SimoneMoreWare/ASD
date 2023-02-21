//NON SONO SICURO CHE FUNZIONI CON TUTTI I CASI DI TEST DI QUESTO MONDO; INOLTRE HO INTESO IL CAMMINO IN MODO DIVERSO DALL ES DEL DIAMETRO
#include <stdio.h>
#include "T.h"

int main() {
    TREE t;
    t = init();
    int length = f(t);
    printf("La lunghezza del cammino piu lungo e: %d\n", length);
    return 0;
}
