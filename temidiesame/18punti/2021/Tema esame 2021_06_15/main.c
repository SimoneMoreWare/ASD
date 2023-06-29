#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pacchi.h"
#include "Magazzino.h"

typedef enum {posizione, inserisci, estrai, sposta, compatta, fine}Comando;

Comando leggiComando();
Comando stringToEnum(char *comando);

int main()
{
    Pacchi p;
    Pacco *pa;
    Magazzino m;
    FILE *f, *f2;
    char pacco[CAR], scaffale[CAR], scaffale2[CAR];
    int corridoio, slot, corridoio2;
    Comando comando_e;

    f=fopen("pacchi.txt", "r");
    if(f==NULL){
        printf("Errore nell'apertura del file.");
        exit(EXIT_FAILURE);
    }

    p=PACCHIread(f);
    fclose(f);

    f2=fopen("magazzino.txt", "r");
    if(f2==NULL){
        printf("Errore nell'apertura del file.");
        exit(EXIT_FAILURE);
    }

    m=MAGAZZINOread(f2);
    fclose(f2);

    do{
        comando_e=leggiComando();
        switch(comando_e){
            case posizione:
                printf("\n---PACCHI:---\n");
                PACCHIprintCode(p, stdout);
                printf("\nDi quale pacco vuoi vedere la posizione? ");
                scanf("%s", pacco);
                pa=PACCHIsearchPacco(p, pacco);
                if(pa==NULL){
                    printf("\nIl pacco %s non esiste.\n", pacco);
                    break;
                }
                PACCOprintPosizione(*pa, stdout);
                break;


            case inserisci:
                printf("\n---PACCHI:---\n");
                PACCHIprintCode(p, stdout);
                printf("\nQuale pacco vuoi posizionare? ");
                scanf("%s", pacco);
                pa=PACCHIsearchPacco(p, pacco);
                if(pa==NULL){
                    printf("\nIl pacco %s non esiste.\n", pacco);
                    break;
                }
                if(POSIZIONEisEmpty(PACCOgetPosizione(*pa))==FALSO){
                    printf("\nIl pacco %s e' gia' stato posizionato nel magazzino.\n", pacco);
                    break;
                }
                printf("\n---MAGAZZINO---\n");
                MAGAZZINOprint(m, stdout);
                printf("\nInserisci la posizione:\n");
                printf("\t- CORRIDOIO: ");
                scanf("%d", &corridoio);
                printf("\t- SCAFFALE: ");
                scanf("%s", scaffale);
                printf("\t- SLOT: ");
                scanf("%d", &slot);
                if(MAGAZZINOinserisciPacco(m, pa, POSIZIONEcrea(corridoio, scaffale, slot))==VERO){
                    printf("\nInserimento avvenuto con successo.\n");
                }
                break;



            case estrai:
                printf("\n---PACCHI:---\n");
                PACCHIprintCode(p, stdout);
                printf("\nQuale pacco vuoi estrarre? ");
                scanf("%s", pacco);
                pa=PACCHIsearchPacco(p, pacco);
                if(pa==NULL){
                    printf("\nIl pacco %s non esiste.\n", pacco);
                    break;
                }
                MAGAZZINOeliminaPacco(m, pa);
                break;



            case sposta:
                printf("\n---PACCHI:---\n");
                PACCHIprintCode(p, stdout);
                printf("\nQuale pacco vuoi spostare? ");
                scanf("%s", pacco);
                pa=PACCHIsearchPacco(p, pacco);
                if(pa==NULL){
                    printf("\nIl pacco %s non esiste.\n", pacco);
                    break;
                }
                if(POSIZIONEisEmpty(PACCOgetPosizione(*pa))==VERO){
                    printf("\nImpossibile spostare il pacco %s in quanto non e' ancora stato posizionato nel magazzino.\n", pacco);
                    break;
                }
                printf("\n---POSIZIONE ATTUALE---\n");
                PACCOprintPosizione(*pa, stdout);
                printf("\n---MAGAZZINO---\n");
                MAGAZZINOprint(m, stdout);
                printf("\nInserisci la nuova posizione:\n");
                printf("\t- CORRIDOIO: ");
                scanf("%d", &corridoio);
                printf("\t- SCAFFALE: ");
                scanf("%s", scaffale);
                printf("\t- SLOT: ");
                scanf("%d", &slot);
                MAGAZZINOspostaPacco(m, pa, POSIZIONEcrea(corridoio, scaffale, slot));
                break;



            case compatta:
                printf("\n---MAGAZZINO---\n");
                MAGAZZINOprint(m, stdout);
                printf("\nQuale scaffali vuoi compattare? Inserisci:\n");
                printf("\t- CORRIDOIO 1: ");
                scanf("%d", &corridoio);
                printf("\t- SCAFFALE 1: ");
                scanf("%s", scaffale);
                printf("\nInserisci:\n");
                printf("\t- CORRIDOIO 2: ");
                scanf("%d", &corridoio2);
                printf("\t- SCAFFALE 2: ");
                scanf("%s", scaffale2);
                MAGAZZINOcompattaScaffali(m, corridoio, scaffale, corridoio2, scaffale2);
                break;



            case fine:
                printf("\nProgramma terminato.\n");
                break;



            default:
                printf("\nComando errato. Reinseriscilo.\n");
       }
       printf("\n");
    }while(comando_e!=fine);

    PACCHIfree(p);
    MAGAZZINOfree(m);
    return 0;
}




Comando leggiComando(){
    int i;
    char comando[CAR];
    char *menu[6]={"'posizione' per ricercare la posizione di un pacco, dato il codice;",
                   "'inserisci' per inserire un pacco in una data posizione;",
                   "'estrai' per estrarre un pacco da una data posizione;",
                   "'sposta' per spostare un pacco da una posizione a un'altra;",
                   "'compatta' per compattare i contenuti di due scaffali in uno solo;",
                   "'fine' per terminare."};
    printf("Scrivi:\n");
    for(i=0; i<6; i++){
        printf("%d) %s\n", i+1, menu[i]);
    }
    printf("\nCosa vuoi fare?: ");
    scanf("%s", comando);
    return stringToEnum(comando);
}




Comando stringToEnum(char *comando){
    if(strcmp(comando, "posizione")==0)
        return posizione;
    else if(strcmp(comando, "inserisci")==0)
        return inserisci;
    else if(strcmp(comando, "estrai")==0)
        return estrai;
    else if(strcmp(comando, "sposta")==0)
        return sposta;
    else if(strcmp(comando, "compatta")==0)
        return compatta;
    else if(strcmp(comando, "fine")==0)
        return fine;
    return -1;
}
