#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produttori.h"

typedef enum{stampa_prod, stampa_mod, canc_prod, canc_mod, canc_acc, incorpora, fine}Comando;

Comando leggiComando();
Comando fromStringToEnum(char *comando);

int main()
{
    Produttori p;
    FILE *f;
    Comando comando_e;
    char prod1[MAX], prod2[MAX], mod[MAX], acc[MAX];
    Produttore pr;
    Modello m;

    f=fopen("produttori.txt", "r");
    if(f==NULL) exit(EXIT_FAILURE);

    p=PRODUTTORIread(f);


    do{
        if(PRODUTTORIsize(p)==0){
            printf("Impossibile eseguire operazioni: la base dati e' vuota.\n");
        }

        comando_e=(PRODUTTORIsize(p)==0)?fine:leggiComando();

        switch(comando_e){
            case stampa_prod:
                printf("\nInserisci il nome di un produttore: ");
                gets(prod1);
                pr=PRODUTTORIcercaProduttore(p, prod1);
                if(PRODUTTOREisNull(pr)==VERO){
                    printf("\nIl produttore %s non esiste.\n", prod1);
                    break;
                }
                printf("\n");
                PRODUTTOREprint(pr, stdout);
                break;

            case stampa_mod:
                printf("\nInserisci il nome di un produttore: ");
                gets(prod1);
                pr=PRODUTTORIcercaProduttore(p, prod1);
                if(PRODUTTOREisNull(pr)==VERO){
                    printf("\nIl produttore %s non esiste.\n", prod1);
                    break;
                }
                printf("\nInserisci il nome di un modello: ");
                gets(mod);
                m=MODELLIcercaModello(PRODUTTOREgetModelli(pr), mod);
                if(MODELLOisNull(m)==VERO){
                   printf("\nIl modello %s non esiste.\n", mod);
                    break;
                }
                printf("\n");
                MODELLOprint(m, stdout);
                break;

            case canc_prod:
                printf("\nInserisci il nome di un produttore: ");
                gets(prod1);
                PRODUTTORIeliminaProduttore(p, prod1);
                break;

            case canc_mod:
                printf("\nInserisci il nome di un produttore: ");
                gets(prod1);
                pr=PRODUTTORIcercaProduttore(p, prod1);
                if(PRODUTTOREisNull(pr)==VERO){
                    printf("\nIl produttore %s non esiste.\n", prod1);
                    break;
                }
                printf("\nInserisci il nome di un modello: ");
                gets(mod);
                MODELLIcancellaModello(PRODUTTOREgetModelli(pr), mod);
                break;

            case canc_acc:
                printf("\nInserisci il nome di un produttore: ");
                gets(prod1);
                pr=PRODUTTORIcercaProduttore(p, prod1);
                if(PRODUTTOREisNull(pr)==VERO){
                    printf("\nIl produttore %s non esiste.\n", prod1);
                    break;
                }
                printf("\nInserisci il nome di un modello: ");
                gets(mod);
                m=MODELLIcercaModello(PRODUTTOREgetModelli(pr), mod);
                if(MODELLOisNull(m)==VERO){
                   printf("\nIl modello %s non esiste.\n", mod);
                    break;
                }
                printf("\nInserisci il nome di un accessorio: ");
                gets(acc);
                ACCESSORIcancellaAccessorio(MODELLOgetAccessori(m), acc);
                break;

            case incorpora:
                printf("\nInserisci il nome di un produttore: ");
                gets(prod1);
                printf("\nInserisci il nome di un altro produttore: ");
                gets(prod2);
                while(strcmp(prod1, prod2)==0){
                    printf("\nI due produttori non possono essere uguali.\n");
                    printf("Inserisci il nome di un altro produttore: ");
                    gets(prod2);

                }
                PRODUTTORIcompattaProduttori(p, prod1, prod2);
                break;

            case fine:
                printf("\nProgramma terminato.\n");
                break;

            default:
                printf("\nComando errato. Reinseriscilo.\n");
        }
        printf("\n");
    }while(comando_e!=fine);
    return 0;
}




Comando leggiComando(){
    char comando[MAX];
    int i;
    char *menu[7]={"'stampa_prod' per leggere da tastiera il nome di un produttore e stampare l’elenco dei modelli da esso prodotti;",
                   "'stampa_mod' per leggere da tastiera il nome di un modello e stampare l’elenco l’elenco degli accessori ad esso associati;",
                   "'canc_prod' per cancellare un produttore, i modelli ad esso relativi e gli accessori associati a quei modelli;",
                   "'canc_mod' per cancellare un modello e gli accessori ad esso associati;",
                   "'canc_acc' per cancellare un accessorio;",
                   "'incorpora' per incorporare un produttore in un altro;",
                   "'fine' per terminare."};

    printf("Scrivi:\n");
    for(i=0; i<7; i++){
        printf("%d) %s\n", i+1, menu[i]);
    }
    printf("\nChe cosa vuoi fare? ");
    gets(comando);
    return fromStringToEnum(comando);
}




Comando fromStringToEnum(char *comando){
    if(strcmp(comando, "stampa_prod")==0)
        return stampa_prod;
    if(strcmp(comando, "stampa_mod")==0)
        return stampa_mod;
    if(strcmp(comando, "canc_prod")==0)
        return canc_prod;
    if(strcmp(comando, "canc_mod")==0)
        return canc_mod;
    if(strcmp(comando, "canc_acc")==0)
        return canc_acc;
    if(strcmp(comando, "incorpora")==0)
        return incorpora;
    if(strcmp(comando, "fine")==0)
        return fine;
    return -1;
}
