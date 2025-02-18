#include "equipArray.h"

/* ADT di prima classe collezione di oggetti di equipaggiamento */
struct equipArray_s {
    int equipped[EQUIP_SLOT];
    int N;
};

/* creatore e disruttore */
equipArray_t equipArray_init() {
    int i;
    equipArray_t equipArray = (equipArray_t) malloc(sizeof(equipArray_i));
    for(i = 0; i < EQUIP_SLOT; i++) {
        equipArray->equipped[i] = -1;
    }
    equipArray->N = 0;
    return equipArray;
}

void equipArray_free(equipArray_t equipArray) {
    free(equipArray);
}

/* quanti equipaggiamenti sono in uso */
int equipArray_inUse(equipArray_t equipArray) {
    return equipArray->N;
}

/* scrittura su file */
void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray) {
    int i;

    for(i = 0; i < equipArray->N; i++) {
        invArray_printByIndex(fp, invArray, equipArray->equipped[i]);
    }
}

/* modifica equipaggiamento scegliendo un oggetto da inventario */
void equipArray_update(equipArray_t equipArray, invArray_t invArray) {
    int i, j, scelta = 1;
    char nome[LEN];

    printf("Inserisci l'indice dell'equipaggiamento da modificare: ");
    scanf("%d", &i);

    if(i >= 0 && i < EQUIP_SLOT) {
        if(equipArray->equipped[i] != -1) {
            printf("Vuoi eliminare (0) o cambiare (1) l'oggetto?");
            scanf("%d", &scelta);
        }

        if(!scelta) {
            equipArray->equipped[i] = -1;
        } else {
            printf("Inserisci il nome dell'oggetto nell'inventario: ");
            scanf("%s", nome);
            equipArray->equipped[i] = invArray_searchByName(invArray, nome);
        }
    }
}

/* torna indice (nel vettore inventario) dell'oggetto in posizione index (0..EQUIP_SLOT-1) di equipArray */
int equipArray_getEquipByIndex(equipArray_t equipArray, int index) {
    return equipArray->equipped[index];
}
