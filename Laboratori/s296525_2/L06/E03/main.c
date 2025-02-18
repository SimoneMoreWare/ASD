#ifndef mod_stats
    #define mod_stats
    #include "stats.h"
#endif

#ifndef mod_inv
    #define mod_inv
    #include "inv.h"
#endif

#ifndef mod_pg
    #define mod_pg
    #include "pg.h"
#endif

typedef enum {
    end_program = 1,
    add_character,
    del_character,
    add_item_character,
    del_item_character,
    pnt_character
} scelta;

int main() {
    tabPg *tabP = TABPGinit();
    tabInv *tabI = TABINVinit();
    int s = 0;
    char code[MAX_LENGTH_CODE], namePG[MAX_LENGTH_PG], pgClass[MAX_LENGTH_PG], nameItem[MAX_LENGTH_ITEM];
    int hp, mp, atk, def, mag, spr;
    link tmp;

    do {
        printf("Scegli una delle seguenti opzioni: \n"
               "1. Termina il programma;\n"
               "2. Aggiungi personaggio;\n"
               "3. Elimina personaggio;\n"
               "4. Assegna un oggetto ad un personaggio;\n"
               "5. Rimuovi un oggetto da un personaggio;\n"
               "6. Stampa le informazioni di un personaggio.\n");
        scanf("%d", &s);

        switch(s) {
            case end_program:
                printf("Terminando il programma...");
                TABPGfree(tabP);
                TABINVfree(tabI);
                break;

            case add_character:
                printf("Codice (PGXXXX): ");
                scanf("%s", code);

                printf("Nome: ");
                scanf("%s", namePG);
                
                printf("Classe: ");
                scanf("%s", pgClass);
                
                printf("HP: ");
                scanf("%d", &hp);
                
                printf("MP: ");
                scanf("%d", &mp);

                printf("ATK: ");
                scanf("%d", &atk);
                
                printf("DEF: ");
                scanf("%d", &def);
                
                printf("MAG: ");
                scanf("%d", &mag);
                
                printf("SPR: ");
                scanf("%d", &spr);

                if((tmp = PGget(code, namePG, pgClass, hp, mp, atk, def, mag, spr)) != NULL) {
                    PGinsert(tabP, tmp);
                    printf("Personaggio inserito correttamente.");
                } else
                    printf("Si e' presentato un errore nell'inserimento del personaggio.");

                break;

            case del_character:
                printf("Codice del personaggio (PGXXXX): ");
                scanf("%s", code);

                PGdelete(tabP, code);
                break;
            
            case add_item_character:
                printf("Codice del personaggio (PGXXXX): ");
                scanf("%s", code);

                printf("Nome dell'oggetto: ");
                scanf("%s", nameItem);

                PGgainItem(tabP, code, *tabI, nameItem);
                break;
            
            case del_item_character:
                printf("Codice del personaggio (PGXXXX): ");
                scanf("%s", code);

                printf("Nome dell'oggetto: ");
                scanf("%s", nameItem);

                PGremoveItem(tabP, code, *tabI, nameItem);
                break;
            
            case pnt_character:
                printf("Codice del personaggio (PGXXXX): ");
                scanf("%s", code);

                PGprint(*tabP, code);
                break;
            
            default:
                printf("Non è stata effettuata una scelta valida!");
        }
    } while(s != end_program);
    return 0;
}